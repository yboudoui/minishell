/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:05:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/18 19:11:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "minishell.h"

static void	signal_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_global.exit_code = 130;
}

static int	heredoc_commande(t_commande cmd)
{
	t_token_list	redir;
	int				*last;

	last = NULL;
	redir = (t_token_list)cmd->redir;
	while (redir)
	{
		if (redir->token->type & TOKEN_HERE_DOCUMENT)
		{
			if (heredoc_read(redir->token))
			{
				if (last)
					close_fd(last);
				last = &redir->token->fd;
			}
			else
				return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_prompt cmd)
{
	struct sigaction		old;
	const struct sigaction	sigint = {
		.sa_handler = signal_control_c,
		.sa_flags = SA_RESETHAND
	};

	sigaction(SIGINT, &sigint, &old);
	g_global.save_stdin = dup(STDIN_FILENO);
	while (cmd)
	{
		if (heredoc_commande(cmd->content))
		{
			sigaction(SIGINT, &old, NULL);
			close(STDIN_FILENO);
			dup2(g_global.save_stdin, STDIN_FILENO);
			close(g_global.save_stdin);
			return (EXIT_FAILURE);
		}
		cmd = cmd->next;
	}
	close(STDIN_FILENO);
	dup2(g_global.save_stdin, STDIN_FILENO);
	close(g_global.save_stdin);
	sigaction(SIGINT, &old, NULL);
	return (EXIT_SUCCESS);
}

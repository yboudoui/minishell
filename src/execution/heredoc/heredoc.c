/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:05:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/01 16:28:23 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	stop = 0;

static void	signal_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDERR_FILENO, "\n", 1); // sortie d'erreur!!!
	close(STDIN_FILENO);
	stop = 1;
}

static int	heredoc_read(t_token token)
{
	int		fds[2];
	int		*new;
	char	*line;

	if (token->type != TOKEN_HERE_DOCUMENT)
		return (EXIT_SUCCESS);
	str_new_empty(&line);
	if (pipe(fds))
		return (EXIT_FAILURE);
	new = ft_calloc(1, sizeof(int));
	if (new == NULL)
		return (EXIT_FAILURE);
	(*new) = fds[0];
	while (line && string_cmp(line, token->input))
	{
		free(line);
		rl_on_new_line();
		line = readline("> ");
		if (stop || line == NULL)
		{
			close(fds[0]);
			close(fds[1]);
			return (EXIT_FAILURE);
		}
//		expand_all_command(env, prompt->commande);
		if (!is_empty(line))
			add_history(line);
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
	}
	free(token->input);
	token->input = new;
	return (close(fds[1]), EXIT_SUCCESS);
}

static int	heredoc_commande(t_commande cmd)
{
	t_list	redir_in;

	redir_in = cmd->redir_in;
	while (redir_in)
	{
		if (heredoc_read(redir_in->content))
			return (EXIT_FAILURE);
		redir_in = redir_in->next;
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_prompt cmd)
{
	int						pid;
	const struct sigaction	sigint = {
		.sa_handler = signal_control_c
	};

	pid = fork();
	if (pid == 0)
	{
		sigaction(SIGINT, &sigint, NULL);
		while (cmd)
		{
			if (heredoc_commande(cmd->content))
				return (EXIT_FAILURE);
			cmd = cmd->next;
		}
		return (EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

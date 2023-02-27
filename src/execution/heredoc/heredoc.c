/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:05:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 12:27:19 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

#include "show.h"
#include <stdio.h>

int	stop = 0;

static void	signal_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDERR_FILENO, "\n", 1); // sortie d'erreur!!!
	close(STDIN_FILENO);
	stop = 1;
}

static int	heredoc_read(int fd, t_token token)
{
	char	*line;

	str_new_empty(&line);
	while (line && string_cmp(line, token->input))
	{
		free(line);
		if (stop)
			return (close(fd), EXIT_FAILURE);
		rl_on_new_line();
		line = readline("> ");
		if (line == NULL)
			return (close(fd), EXIT_FAILURE);
//		expand_all_command(env, prompt->commande);
		if (!is_empty(line))
			add_history(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	return (close(fd), EXIT_SUCCESS);
}

static int	heredoc_commande(t_commande cmd)
{
	t_list	heredoc;

	heredoc = cmd->heredoc.list;
	if (heredoc == NULL)
		return (EXIT_SUCCESS);
	cmd->heredoc.pipe = ft_calloc(2, sizeof(int));
	if (cmd->heredoc.pipe == NULL)
		return (EXIT_FAILURE);
	while (heredoc)
	{
		if (pipe(cmd->heredoc.pipe))
			return (EXIT_FAILURE);
		if (heredoc_read(cmd->heredoc.pipe[1], heredoc->content))
			break ;
//			return (EXIT_FAILURE);
		heredoc = heredoc->next;
		if (heredoc)
			close(cmd->heredoc.pipe[0]);
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

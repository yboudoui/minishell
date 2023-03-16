/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:33:35 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/16 15:39:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	execute(char *argv[], t_pipex *pipex)
{
	const struct sigaction sa = {
		.sa_handler = SIG_IGN
	};

	pipe_fd(pipex, pipex->fd);
	if (argv != NULL && !pipex->redir_error)
		pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	if (pipex->cmd_path == NULL)
		pipex->exitcode = CMD_NOT_FOUND;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	fork_pid(&pipex->pid[pipex->i]);
	if (pipex->pid[pipex->i] == 0)
	{
		sigaction(SIGINT, &g_global.default_sigint, NULL);
		sigaction(SIGQUIT, &g_global.default_sigquit, NULL);
		exec_cmd(pipex, argv);
	}
	dup_fd(pipex->fd[0], STDIN_FILENO);
	close_fd(&pipex->fd[1]);
	close_fd(&pipex->fd[0]);
	close_fd(&pipex->infile);
	close_fd(&pipex->outfile);
	f_free((void **)&pipex->cmd_path);
	return (EXIT_SUCCESS);
}

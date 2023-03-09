/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:33:35 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/09 19:00:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	run_builtin(t_pipex *pipex, char **argv)
{
	g_global.exit_code = pipex->builtin(argv);
	return (0);
}

static inline int	is_error(t_pipex *pipex, char **argv)
{
	if (pipex->infile == -1)
		return (1);
	if (pipex->outfile == -1)
		return (1);
	if (argv == NULL)
		return (1);
	return (0);
}

int	execute(char *argv[], t_pipex *pipex)
{
	struct sigaction	new_action;
	struct sigaction	old_action;

	if (is_error(pipex, argv))
		return (-1);
	pipe_fd(pipex, pipex->fd);
	/* if (pipex->path == false) */
	/* { */
	/* 	generic_err(argv[0], "No such file or directory", 2); */
	/* 	return (EXIT_FAILURE); */
	/* } */
	pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	if (pipex->cmd_path == NULL)
		g_global.exit_code = CMD_NOT_FOUND;
	fork_pid(&pipex->pid[pipex->i]);
	if (pipex->pid[pipex->i] == 0)
	{
		new_action.sa_handler = signal_handler;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, &old_action);
		sigaction(SIGQUIT, &new_action, &old_action);
		exec_cmd(pipex, argv);
		return (EXIT_FAILURE);
	}
	free(pipex->cmd_path);
	dup_fd(pipex->fd[0], STDIN_FILENO);
	close_fd(&pipex->fd[1]);
	close_fd(&pipex->fd[0]);
	return (EXIT_SUCCESS);
}

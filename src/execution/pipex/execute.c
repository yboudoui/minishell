/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:33:35 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/12 17:15:46 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	run_builtin(t_pipex *pipex, char **argv)
{
	g_global.exit_code = pipex->builtin(argv);
	return (0);
}

/* static inline int	is_error(t_pipex *pipex, char **argv) */
/* { */
/* 	if (pipex->redir_error) */
/* 		return (1); */
/* 	if (argv == NULL) */
/* 	{ */
/* 		printf("argv == NULL\n"); */
/* 		return (1); */
/* 	} */
/* 	return (0); */
/* } */

int	execute(char *argv[], t_pipex *pipex)
{
	const struct sigaction sa = {
		.sa_handler = SIG_IGN
	};

	/* if (is_error(pipex, argv)) */
	/* 	return (-1); */
	pipe_fd(pipex, pipex->fd);
	if (argv != NULL)
		pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	/* printf("cmd_path = %s\n", pipex->cmd_path); */
	if (pipex->cmd_path == NULL)
		pipex->exitcode = CMD_NOT_FOUND;
	/* if (argv == NULL) */
	/* { */
	/* 	close_fd(&pipex->infile); */
	/* 	close_fd(&pipex->outfile); */
	/* } */
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
	return (EXIT_SUCCESS);
}

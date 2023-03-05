/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/05 19:59:24 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"
#include <unistd.h>

static inline int manage_pipeline_fds(t_pipex *pipex, t_cmd cmd)
{
	int	fd;
	fd = infile(cmd->redir_in);
	if (fd == 1)
	{
		pipex->infile = fd;
		return (0);
	}
	else if (fd == -1)
	{
		pipex->infile = -1;
		return (0);
	}
	else
	{
		pipex->infile = fd;
		return (0);
	}
}

int	pipex(t_env_list env, t_prompt prompt)
{
	t_pipex					pipex;
	t_cmd					cmd;
	static const t_pipex	EMPTY_PIP;

	pipex = EMPTY_PIP;
	/* pipex.stdin_fd = dup(STDIN_FILENO); */
	pipex.argc = list_size((t_list)prompt);
	while (prompt)
	{
		pipex.paths = get_paths(env, &pipex);
		pipex.env = env;
		cmd = cmd_create(prompt->content);
		manage_pipeline_fds(&pipex, cmd);
		pipex.i++;
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		if (pipex.infile != -1 && pipex.outfile != -1)
			execute(cmd->argv, &pipex);
		cmd_destroy(cmd);
		prompt = prompt->next;
	}
	while (waitpid(0, NULL, 0) != -1)
		;
	/* free(pipex.paths); */
	/* dup_fd(pipex.stdin_fd, STDIN_FILENO); */
	/* close_fd(&pipex.stdin_fd); */
	return (EXIT_SUCCESS);
}

int	execute(char *argv[], t_pipex *pipex)
{
	pid_t	pid;

	if (argv == NULL)
		return (EXIT_SUCCESS);
	pipe_fd(pipex, pipex->fd);
	pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	if (pipex->cmd_path == NULL)
	{
		exit_code = CMD_NOT_FOUND;
		return (EXIT_FAILURE);
	}
	fork_pid(&pid);
	if (pid == 0)
	{
		close_fd(&pipex->fd[0]);
		exec_cmd(pipex, argv);
		return (EXIT_FAILURE);
	}
	close_fd(&pipex->fd[1]);
	pipex->prevpipe = dup(pipex->fd[0]);
	close_fd(&pipex->fd[0]);
	return (EXIT_SUCCESS);
}

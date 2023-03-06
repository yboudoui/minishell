/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/06 13:22:54 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"
#include <stdlib.h>
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

int	init_exec(t_pipex *pipex)
{
	pipex->pid = malloc(sizeof(pid_t) * pipex->argc);
	if (!pipex->pid)
	{
		generic_err("malloc", NULL, 2);
		return (-1);
	}
	return (0);
}

int	waitall(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->argc)
	{
		waitpid(pipex->pid[i], &pipex->status, 0);
		i++;
	}
	return (0);
}

int	pipex(t_env_list env, t_prompt prompt)
{
	t_pipex					pipex;
	t_cmd					cmd;
	static const t_pipex	empty_pipex;

	pipex = empty_pipex;
	pipex.stdin_fd = dup(STDIN_FILENO);
	pipex.argc = list_size((t_list)prompt);
	pipex.paths = get_paths(env, &pipex);
	if (init_exec(&pipex) == -1)
		return (EXIT_FAILURE);
	while (prompt)
	{
		pipex.env = env;
		cmd = cmd_create(prompt->content);
		manage_pipeline_fds(&pipex, cmd);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		if (pipex.infile != -1 || pipex.outfile != -1)
			execute(cmd->argv, &pipex);
		cmd_destroy(cmd);
		prompt = prompt->next;
		pipex.i++;
	}
	waitall(&pipex);
	/* free(pipex.paths); */
	dup_fd(pipex.stdin_fd, STDIN_FILENO);
	close_fd(&pipex.stdin_fd);
	return (EXIT_SUCCESS);
}

int	execute(char *argv[], t_pipex *pipex)
{
	if (argv == NULL)
		return (EXIT_SUCCESS);
	pipe_fd(pipex, pipex->fd);
	pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	if (pipex->cmd_path == NULL)
	{
		exit_code = CMD_NOT_FOUND;
		return (EXIT_FAILURE);
	}
	fork_pid(&pipex->pid[pipex->i]);
	if (pipex->pid[pipex->i] == 0)
	{
		exec_cmd(pipex, argv);
		return (EXIT_FAILURE);
	}
	dup_fd(pipex->fd[0], STDIN_FILENO);
	close_fd(&pipex->fd[1]);
	close_fd(&pipex->fd[0]);
	return (EXIT_SUCCESS);
}

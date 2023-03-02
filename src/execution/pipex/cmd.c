/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:51:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/02 16:31:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static inline int cmd_in(t_pipex *pipex)
{
	if (pipex->infile > 2)
	{
		if (dup_fd(pipex->infile, STDIN_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->infile) == -1)
			return (-1);
	}
	if (pipex->infile == 1 && pipex->i != 0)
	{
		if (dup_fd(pipex->fd[0], STDIN_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->fd[0]) == -1)
			return (-1);
	}
	return (0);
}

static inline int cmd_out(t_pipex *pipex)
{
	if (pipex->outfile > 2)
	{
		if (dup_fd(pipex->outfile, STDOUT_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->outfile) == -1)
			return (-1);
	}
	if (pipex->i == pipex->argc)
	{
		return (0);
	}
	if (pipex->outfile == 1 && pipex->i != pipex->argc)
	{
		if (dup_fd(pipex->fd[1], STDOUT_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->fd[1]) == -1)
			return (-1);
	}
	return (0);
}

int exec_cmd(t_pipex *pipex, char **argv)
{
	char *cmd_path;

	if (cmd_in(pipex) == -1)
		return (-1);
	if (cmd_out(pipex) == -1)
		return (-1);
	cmd_path = get_cmd_path(pipex, argv[0]);
	if (cmd_path == NULL)
		return (EXIT_FAILURE);
	if (execve(cmd_path, argv, parse_env(pipex->env)) == -1)
		return (generic_err("execve", NULL, 1));
	return (-1);
}

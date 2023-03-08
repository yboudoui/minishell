/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:51:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/07 15:23:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static inline int	cmd_in(t_pipex *pipex)
{
	if (pipex->infile > 2)
	{
		if (dup_fd(pipex->infile, STDIN_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->infile) == -1)
			return (-1);
		if (close_fd(&pipex->fd[0]) == -1)
			return (-1);
	}
	else
	{
		if (close_fd(&pipex->fd[0]) == -1)
			return (-1);
	}
	return (0);
}

static inline int	cmd_out(t_pipex *pipex)
{
	if (pipex->outfile > 2)
	{
		if (dup_fd(pipex->outfile, STDOUT_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->outfile) == -1)
			return (-1);
		if (close_fd(&pipex->fd[1]) == -1)
			return (-1);
	}
	else if (pipex->i == pipex->argc - 1)
	{
		if (close_fd(&pipex->fd[1]) == -1)
			return (-1);
		return (0);
	}
	else if (pipex->i != pipex->argc - 1)
	{
		if (dup_fd(pipex->fd[1], STDOUT_FILENO) == -1)
			return (-1);
		if (close_fd(&pipex->fd[1]) == -1)
			return (-1);
	}
	return (0);
}

int	exec_cmd(t_pipex *pipex, char **argv)
{
	if (cmd_in(pipex) == -1)
		return (-1);
	if (cmd_out(pipex) == -1)
		return (-1);
	if (pipex->cmd_path == NULL)
		return (EXIT_FAILURE);
	if (execve(pipex->cmd_path, argv, parse_env()) == -1)
		return (generic_err("execve", NULL, 1));
	return (-1);
}

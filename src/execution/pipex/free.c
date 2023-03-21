/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:58:49 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/21 15:33:39 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	free_pipex(t_pipex *pipex)
{
	dup_fd(pipex->stdin_fd, STDIN_FILENO);
	close_fd(&pipex->stdin_fd);
	if (!pipex)
		return (-1);
	if (pipex->infile > 2)
		close_fd(&pipex->infile);
	if (pipex->outfile > 2)
		close_fd(&pipex->outfile);
	if (pipex->pid)
		f_free((void **)&pipex->pid);
	if (pipex->cmd_path)
		f_free((void **)&pipex->cmd_path);
	close_fd(&pipex->fd[1]);
	close_fd(&pipex->fd[0]);
	string_array_destroy(pipex->paths);
	pipex->paths = NULL;
	f_free((void **)&pipex);
	return (0);
}

int	f_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (0);
	}
	else
		return (-1);
}

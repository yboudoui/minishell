/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:39:52 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/26 12:30:07 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../inc/minishell.h"

typedef struct s_pipex
{
	char	**paths;
	bool	path;
	int		fd[2];
	int		infile;
	int		outfile;
	t_list	env;
}	t_pipex;

void	path_null(t_pipex *pipex, char *cmd);

void	execute(char **argv, t_pipex *pipex);

void	close_fd(int *fd);

void	pipe_fd(t_pipex *pipex, int *fd);

void	fork_pid(int *pid);

void	dup_fd(int fd, int new_fd);

char	**get_paths(t_list env, t_pipex *pipex);

int		infile(t_list redir_in);

int		outfile(t_list redir_out);

int		f_open(char *file, int flag, int mode);

void	generic_err(char *str, int system);

#endif
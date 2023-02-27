/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:39:52 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 17:07:54 by kdhrif           ###   ########.fr       */
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
	int		status;
	int		argc;
	int	 	remove;
	t_list	env;
}	t_pipex;

typedef struct s_prompt	*t_prompt;

char	**get_paths(t_list env, t_pipex *pipex);

void	pipex(t_list env, t_prompt prompt);

void	pipeline_status(t_pipex *pipex, int i, int pid);

void	path_null(t_pipex *pipex, char *cmd);

void	execute(char **argv, t_pipex *pipex, int i);

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

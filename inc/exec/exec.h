/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:39:52 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/28 17:42:43 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../inc/minishell.h"

typedef struct s_pipex
{
	char	**paths;
	char	**argv;
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

int		is_dir(char *path);

void	null_str_err(char *str);

char	**parse_env(t_list env);

int		exec_cmd(t_pipex *pipex, char **argv, int in, int out);

char	*get_cmd_path(t_pipex *pipex, char *cmd);

char	**get_paths(t_list env, t_pipex *pipex);

void	pipex(t_list env, t_prompt prompt);

void	pipeline_status(t_pipex *pipex, int i, int pid);

void	path_null(t_pipex *pipex, char *cmd);

void	execute(t_list argv, t_pipex *pipex, int i);

void	close_fd(int *fd);

void	pipe_fd(t_pipex *pipex, int *fd);

void	fork_pid(int *pid);

void	dup_fd(int fd, int new_fd);

char	**get_paths(t_list env, t_pipex *pipex);

int		infile(t_list redir_in);

int		outfile(t_list redir_out);

int		f_open(char *file, int flag, int mode);

void	generic_err(char *cmd, char *error, int system);

#endif

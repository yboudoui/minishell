/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:39:52 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/06 18:33:22 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../inc/minishell.h"
# include <sys/types.h>

# define CMD_NOT_FOUND 127

typedef struct s_pipex
{
	char	**paths;
	char	**argv;
	char	*cmd_path;
	pid_t	*pid;
	bool	path;
	int		fd[2];
	int		prevpipe;
	int		stdin_fd;
	int		infile;
	int		outfile;
	int		status;
	int		argc;
	int		remove;
	int		i;
}	t_pipex;

typedef struct s_prompt	*t_prompt;

int		is_dir(char *path);

void	null_str_err(char *str);

char	**parse_env(void);

int		exec_cmd(t_pipex *pipex, char **argv);

char	*get_cmd_path(t_pipex *pipex, char *cmd);

char	**get_paths(t_pipex *pipex);

int		pipex(t_prompt prompt);

void	pipeline_status(t_pipex *pipex, int i, int pid);

void	path_null(t_pipex *pipex, char *cmd);

int		execute(char *argv[], t_pipex *pipex);

int		close_fd(int *fd);

void	pipe_fd(t_pipex *pipex, int *fd);

void	fork_pid(int *pid);

int		dup_fd(int fd, int new_fd);

int		infile(t_list redir_in);

int		outfile(t_list redir_out);

int		f_open(char *file, int flag, int mode);

int		generic_err(char *cmd, char *error, int system);

#endif

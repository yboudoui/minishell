/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:39:52 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/22 16:50:37 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../inc/minishell.h"
# include "cmd.h"
# include <sys/types.h>

# define CMD_NOT_FOUND 127

typedef struct s_flag
{
	bool	is_fork;
}	t_flag;

typedef struct s_pipex
{
	char			**paths;
	char			**argv;
	char			*cmd_path;
	pid_t			*pid;
	t_fp_builtin	builtin;
	bool			path;
	bool			abs_path_cmd;
	bool			redir_error;
	bool			is_dir;
	bool			is_err;
	int				exitcode;
	int				fd[2];
	int				builtin_stdin;
	int				builtin_stdout;
	int				prevpipe;
	int				stdin_fd;
	int				stdout_fd;
	int				infile;
	int				outfile;
	int				status;
	int				argc;
	int				remove;
	int				i;
}	t_pipex;

//redir.c
int		manage_redirs(t_list redir, t_pipex *pipex);

//exec_builtins.c
int		exec_builtins(t_cmd_list cmds, t_pipex *pipex);
int		run_builtin(t_pipex *pipex, char **argv);

//wait.c
int		waitall(t_pipex *pipex);

int		execute(char *argv[], t_pipex *pipex);

int		free_pipex(t_pipex *pipex);
int		f_free(void **ptr);

void	signal_handler(int signum);

int		cmd_out(t_pipex *pipex);

int		cmd_in(t_pipex *pipex);

int		is_dir(char *path);

void	null_str_err(char *str);

char	**parse_env(t_env_list env);

int		exec_cmd(t_pipex *pipex, char **argv);

char	*get_cmd_path(t_pipex *pipex, char *cmd);

char	**get_paths(t_pipex *pipex);

int		pipex(t_cmd_list cmds);

void	pipeline_status(t_pipex *pipex, int i, int pid);

void	path_null(t_pipex *pipex, char *cmd);

int		close_fd(int *fd);

void	pipe_fd(t_pipex *pipex, int *fd);

int		is_fd_open(int fd);

//singleton.c
t_flag	*f(void);

void	fork_pid(int *pid);

int		dup_fd(int fd, int new_fd);

int		infile(t_list redir_in);

int		outfile(t_list redir_out);

int		f_open(char *file, int flag, int mode);

int		generic_err(char *cmd, char *error, int system);

#endif

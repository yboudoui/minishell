/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/11 17:15:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "string.h"

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_shell {
	char	*path;
	char	*name;
	int		fd_out;
	int		pipe[2];
	int		pid;
}	t_shell;

t_shell	shell_create(char *path);
void	shell_write(t_shell shell, char *str);
void	shell_close_stdin(t_shell *shell);
void	shell_close_stdout(t_shell *shell);
void	shell_fork(t_shell *shell, char *env[]);
void	shell_wait_fork(t_shell shell);
#endif

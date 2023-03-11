/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:25:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/11 13:45:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	shell_create(char *path)
{
	t_shell	output;
	char	*filename;

	filename = ft_strjoin(name, ".out");
	output.fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	free(filename);
	pipe(output.pipe);
	return (output);
}

void	shell_write(t_shell shell, char *str)
{
	write(shell.pipe[1], str, ft_strlen(str));
}

void	shell_close_stdin(t_shell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->pipe[1] < 0)
		return ;
	close(shell->pipe[1]);
	shell->pipe[1] = -1;
}

void	shell_close_stdout(t_shell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->fd_out < 0)
		return ;
	close(shell->fd-out);
	shell->fd-out = -1;
}

void	shell_fork(t_shell *shell, char *env[])
{
	if (shell == NULL)
		return ;
	shell->pid = fork();
	if (shell->pid != 0)
		return ;
	dup2(shell->pipe[0], STDIN_FILENO);
	dup2(shell->fd_out, STDOUT_FILENO);
	execve(shell->path, (char *[]){shell->name, NULL}, env);
}

void	shell_wait_fork(t_shell shell)
{
	waitpid(shell.pid, NULL, 0);
}

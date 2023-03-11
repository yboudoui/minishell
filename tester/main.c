/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 06:28:08 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/11 11:27:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum e_shell_kind {
	B_SH,
	M_SH,
	MAX_SH,
}	t_shell_kind;

int	sh(int fd_in, int fd_out, char *path, char *name, char *env[])
{
	int	pid;

	pid = fork();
	if (pid != 0)
		return (pid);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
//	dup2(fd_out, STDERR_FILENO);
	execve(path, (char *[]){name, NULL}, env);
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	int		pid[MAX_SH];
//	int		sh_in[MAX_SH];
	int		sh_out[MAX_SH];
	int		sh_pipe[MAX_SH][2];

	(void)ac;
	(void)av;
	pipe(sh_pipe[B_SH]);
	pipe(sh_pipe[M_SH]);

	sh_out[B_SH] = open("sh_b.out", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	sh_out[M_SH] = open("sh_m.out", O_CREAT | O_WRONLY | O_TRUNC, 0666);

	write(sh_pipe[B_SH][1], "ls\n", 3);
	write(sh_pipe[M_SH][1], "ls\n", 3);
	close(sh_pipe[B_SH][1]);
	close(sh_pipe[M_SH][1]);

	pid[B_SH] = sh(sh_pipe[B_SH][0], sh_out[B_SH], "/bin/bash", "bash", env);
	pid[M_SH] = sh(sh_pipe[M_SH][0], sh_out[M_SH], "../minishell", "minishell", env);

	waitpid(pid[B_SH], NULL, 0);
	waitpid(pid[M_SH], NULL, 0);

	close(sh_out[B_SH]);
	close(sh_out[M_SH]);
}

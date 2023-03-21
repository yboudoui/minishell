/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:51:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/21 12:12:48 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <unistd.h>

int	cmd_in(t_pipex *pipex)
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

int	cmd_out(t_pipex *pipex)
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

int	handle_builtin(t_pipex *pipex, char **argv)
{
	t_fp_builtin	builtin;
	int				exit_code;

	signal(SIGPIPE, SIG_IGN);
	if (ft_strncmp("exit", *argv, ft_strlen("exit")) == 0)
	{
		f()->is_fork = true;
		builtin = pipex->builtin;
		free_pipex(pipex);
		meta_exit(builtin(argv), NULL);
	}
	exit_code = pipex->builtin(argv);
	meta_exit(exit_code, pipex);
	return (0);
}

int	exec_cmd(t_pipex *pipex, char **argv)
{
	char			**env;

	cmd_in(pipex);
	cmd_out(pipex);
	if (pipex->redir_error)
		meta_exit(1, pipex);
	if (argv == NULL)
		meta_exit(0, pipex);
	if (pipex->cmd_path == NULL)
		meta_exit(127, pipex);
	if (pipex->builtin)
		handle_builtin(pipex, argv);
	env = parse_env(env_list_singleton(NULL));
	if (execve(pipex->cmd_path, argv, env) == -1)
	{
		pipex->exitcode = 1;
		string_array_destroy(env);
		meta_exit(pipex->exitcode, pipex);
	}
	string_array_destroy(env);
	meta_exit(pipex->exitcode, pipex);
	return (-1);
}

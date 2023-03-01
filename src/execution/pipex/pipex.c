/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/01 14:23:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"
#include "cmd.h"

int	pipex(t_list env, t_prompt prompt)
{
	t_pipex					pipex;
	t_cmd					cmd;
	static const t_pipex	EMPTY_PIP;
	int						i;

	pipex = EMPTY_PIP;
	pipex.argc = list_size((t_list)prompt);
	pipex.paths = get_paths(env, &pipex);
	pipex.env = env;
	i = 0;
	while (prompt)
	{
		cmd = cmd_create(prompt->content);
		pipex.infile = infile(cmd->redir_in);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		if (pipex.outfile != -1)
			if (execute(cmd->argv, &pipex, i))
				return (EXIT_FAILURE);
		i++;
		cmd_destroy(cmd);
		prompt = prompt->next;
	}
	return (EXIT_SUCCESS);
}

int	execute(char *argv[], t_pipex *pipex, int i)
{
	pid_t	pid;

	if (argv == NULL)
		return (EXIT_SUCCESS);
	pipe_fd(pipex, pipex->fd);
	fork_pid(&pid);
	if (pid == 0)
	{
		close_fd(&pipex->fd[0]);
		if (pipex->outfile == STDOUT_FILENO)
			exec_cmd(pipex, argv, pipex->infile, pipex->outfile);
		else
			exec_cmd(pipex, argv, pipex->infile, pipex->outfile);
		return (EXIT_FAILURE);
	}
	close_fd(&pipex->fd[1]);
	dup_fd(pipex->fd[0], STDIN_FILENO);
	close_fd(&pipex->fd[0]);
	pipeline_status(pipex, i, pid);
	return (EXIT_SUCCESS);
}

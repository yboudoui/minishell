/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/01 16:17:56 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"

int	pipex(t_list env, t_prompt prompt)
{
	t_pipex					pipex;
	t_cmd					cmd;
	static const t_pipex	EMPTY_PIP;

	pipex = EMPTY_PIP;
	pipex.argc = list_size((t_list)prompt);
	pipex.paths = get_paths(env, &pipex);
	pipex.env = env;
	while (prompt)
	{
		cmd = cmd_create(prompt->content);
		pipex.infile = infile(cmd->redir_in);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		if (pipex.infile != -1 && pipex.outfile != -1)
			if (execute(cmd->argv, &pipex))
				return (EXIT_FAILURE);
		pipex.i++;
		cmd_destroy(cmd);
		prompt = prompt->next;
	}
	/* free(pipex.paths); */
	return (EXIT_SUCCESS);
}

int	execute(char *argv[], t_pipex *pipex)
{
	pid_t	pid;

	if (argv == NULL)
		return (EXIT_SUCCESS);
	pipe_fd(pipex, pipex->fd);
	fork_pid(&pid);
	if (pid == 0)
	{
		close_fd(&pipex->fd[0]);
		exec_cmd(pipex, argv);
		return (EXIT_FAILURE);
	}
	else 
	{
		close_fd(&pipex->fd[1]);
		dup_fd(pipex->fd[0], STDIN_FILENO);
		close_fd(&pipex->fd[0]);
		pipeline_status(pipex, pid, pipex->i);
		return (EXIT_SUCCESS);
	}
}

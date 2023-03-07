/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/07 12:24:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	waitall(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->argc)
	{
		if (pipex->pid[i] != -1)
			waitpid(pipex->pid[i], &pipex->status, 0);
		i++;
	}
	return (0);
}

bool	pipex_create(t_prompt prompt, t_pipex *output)
{
	char	*env_path;
	if (prompt == NULL)
		return (output);
	(*output) = (t_pipex){0};
	output->stdin_fd = dup(STDIN_FILENO);
	output->argc = list_size((t_list)prompt);
	env_path = env_get_value("PATH", 0, 0);
	output->paths = ft_split(env_path, ':');
	free(env_path);
	output->pid = ft_calloc(output->argc + 1, sizeof(pid_t));
	if (output->pid == NULL)
		return (generic_err("malloc", NULL, 2), false);
	return (true);
}

int	pipex(t_prompt prompt)
{
	t_pipex					pipex;
	t_cmd					cmd;

	if (!pipex_create(prompt, &pipex))
		return (EXIT_FAILURE);
	while (prompt)
	{
		cmd = cmd_create(prompt->content);
		pipex.infile = infile(cmd->redir_in);
		if (pipex.infile != -1)
			pipex.outfile = outfile(cmd->redir_out);
		if (pipex.infile != -1 || pipex.outfile != -1)
			execute(cmd->argv, &pipex);
		cmd_destroy(cmd);
		prompt = prompt->next;
		pipex.i++;
	}
	waitall(&pipex);
	/* free(pipex.paths); */
	dup_fd(pipex.stdin_fd, STDIN_FILENO);
	close_fd(&pipex.stdin_fd);
	string_array_destroy(pipex.paths);
	free(pipex.pid);
	return (EXIT_SUCCESS);
}

int	execute(char *argv[], t_pipex *pipex)
{
	t_fp_builtin	builtin;

	if (argv == NULL || pipex == NULL)
		return (EXIT_SUCCESS);
	builtin = is_builtin(argv[0]);
	if (builtin)
		return (builtin(argv));
	pipe_fd(pipex, pipex->fd);
	pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	if (pipex->cmd_path == NULL)
	{
		g_exit_code = CMD_NOT_FOUND;
		return (EXIT_FAILURE);
	}
	pipex->pid[pipex->i] = fork();
	if (pipex->pid[pipex->i] == -1)
		generic_err("Fork", NULL, 1);
	if (pipex->pid[pipex->i] == 0)
	{
		exec_cmd(pipex, argv);
		return (EXIT_FAILURE);
	}
	dup_fd(pipex->fd[0], STDIN_FILENO);
	close_fd(&pipex->fd[1]);
	close_fd(&pipex->fd[0]);
	return (EXIT_SUCCESS);
}

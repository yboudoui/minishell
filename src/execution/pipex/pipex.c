/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/13 17:04:26 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	init_exec(t_pipex *pipex)
{
	pipex->pid = ft_calloc(pipex->argc, sizeof(pid_t));
	if (pipex->pid == NULL)
		return (generic_err("malloc", NULL, 2), -1);
	return (0);
}

int	reset_flags(t_pipex *pipex)
{
	pipex->abs_path_cmd = false;
	pipex->redir_error = false;
	pipex->builtin = NULL;
	return (0);
}

int	pipex(t_cmd_list cmds)
{
	t_pipex			*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	g_global.pipex = pipex;
	pipex->argc = list_size((t_list)cmds);
	if (exec_builtins(cmds, pipex))
	{
		f_free((void **)&pipex);
		return (0);
	}
	pipex->stdin_fd = dup(STDIN_FILENO);
	pipex->paths = get_paths(pipex);
	pipex->env = env_list_singleton(NULL);
	if (init_exec(pipex) == -1)
		return (EXIT_FAILURE);
	while (cmds)
	{
		reset_flags(pipex);
		pipex->redir_error = manage_redirs(cmds->cmd->redir, pipex);
		execute(cmds->cmd->argv, pipex);
		cmds = cmds->next;
		pipex->i++;
	}
	waitall(pipex);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_control_c_);
	free_pipex(pipex);
	return (0);
}

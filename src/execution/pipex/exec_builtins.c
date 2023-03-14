/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:47:17 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/14 14:35:27 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <unistd.h>

int	run_builtin(t_pipex *pipex, char **argv)
{
	t_fp_builtin	builtin;

	builtin = is_builtin(argv[0]);
	g_global.exit_code = builtin(argv);
	if (pipex)
	{
		dup_fd(pipex->stdout_fd, STDOUT_FILENO);
		close_fd(&pipex->stdout_fd);
		free_pipex(pipex);
	}
	return (0);
}

int	set_redirs(t_pipex *pipex)
{
	if (pipex->infile > 2)
	{
		dup_fd(pipex->infile, STDIN_FILENO);
		close_fd(&pipex->infile);
	}
	if (pipex->outfile > 2)
	{
		dup_fd(pipex->outfile, STDOUT_FILENO);
		close_fd(&pipex->outfile);
	}
	return (0);
}

int	exec_builtins(t_cmd_list cmds, t_pipex *pipex)
{
	pipex->builtin = NULL;
	if (pipex->argc == 1 && cmds->cmd->argv)
	{
		pipex->builtin = is_builtin(cmds->cmd->argv[0]);
		if (pipex->builtin)
		{
			pipex->stdout_fd = dup(STDOUT_FILENO);
			pipex->redir_error = manage_redirs(cmds->cmd->redir, pipex);
			if (pipex->redir_error)
				return (1);
			set_redirs(pipex);
			if (ft_strncmp(cmds->cmd->argv[0], "exit", 5) == 0)
			{
				dup_fd(pipex->stdout_fd, STDOUT_FILENO);
				close_fd(&pipex->stdout_fd);
				free_pipex(pipex);
				run_builtin(NULL, cmds->cmd->argv);
			}
			else
				run_builtin(pipex, cmds->cmd->argv);
			return (1);
		}
	}
	return (0);
}

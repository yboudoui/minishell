/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:47:17 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/13 19:31:34 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	run_builtin(char **argv)
{
	t_fp_builtin	builtin;

	builtin = is_builtin(argv[0]);
	g_global.exit_code = builtin(argv);
	return (0);
}

int exec_builtins(t_cmd_list cmds, t_pipex *pipex)
{
	pipex->builtin = NULL;
	if (pipex->argc == 1 && cmds->cmd->argv)
	{
		pipex->builtin = is_builtin(cmds->cmd->argv[0]);
		if (pipex->builtin)
		{
			free_pipex(pipex);
			run_builtin(cmds->cmd->argv);
			return (1);
		}
	}
	return (0);
}

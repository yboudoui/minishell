/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:41:48 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/21 11:28:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	meta_exit(int exitcode, t_pipex *pipex)
{
	prompt_destroy(&g_global.prompt);
	cmd_list_destroy(&g_global.cmds);
	env_list_destroy();
	if (pipex)
		free_pipex(pipex);
	exit(exitcode);
}

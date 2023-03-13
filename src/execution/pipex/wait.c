/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:57:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/13 15:58:08 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	waitall(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->argc)
	{
		waitpid(pipex->pid[i], &pipex->status, 0);
		i++;
	}
	if (WIFSIGNALED(pipex->status))
	{
		if (WTERMSIG(pipex->status) == 2)
		{
			g_global.exit_code = 130;
			ft_putstr_fd("\n", 1);
		}
		if (WTERMSIG(pipex->status) == 3)
		{
			g_global.exit_code = 131;
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
	}
	else if (WIFEXITED(pipex->status))
		g_global.exit_code = WEXITSTATUS(pipex->status);
	return (0);
}

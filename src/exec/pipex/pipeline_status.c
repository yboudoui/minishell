/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:00:29 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 14:12:44 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	pipeline_status(t_pipex *pipex, int i, int pid)
{
	if (i == pipex->argc)
		waitpid(pid, &pipex->status, 0);
}

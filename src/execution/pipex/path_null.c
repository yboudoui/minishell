/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:27:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/07 18:28:55 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	path_null(t_pipex *pipex, char *cmd)
{
	(void)cmd;
	if (pipex->path == false && !pipex->builtin)
		generic_err(cmd, "No such file or directory", 2);
	/* printf("this is the pb\n"); */
}

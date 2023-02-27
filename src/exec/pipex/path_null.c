/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:27:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 15:02:14 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	path_null(t_pipex *pipex, char *cmd)
{
	(void)cmd;
	if (pipex->path == false)
		generic_err("No such file or directory", 2);
}

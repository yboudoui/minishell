/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:54:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/09 13:45:19 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	**get_paths(t_pipex *pipex)
{
	char	**paths;
	t_env_var	found;

	found = env_find("PATH", 0, 0);
	pipex->path = false;
	if (found)
	{
		paths = ft_split(found->value, ':');
		if (paths)
		{
			pipex->path = true;
			return (paths);
		}
	}
	return (NULL);
}

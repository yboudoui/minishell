/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:54:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/02 16:14:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	**get_paths(t_env_list env, t_pipex *pipex)
{
	char	**paths;
	char	*path;

	while (env)
	{
		if (ft_strncmp(env->var->name, "PATH", 5) == 0)
		{
			path = ft_strdup(env->var->value);
			if (path == NULL)
				return (NULL);
			paths = ft_split(path, ':');
			if (paths == NULL)
				return (NULL);
			free(path);
			pipex->path = true;
			return (paths);
		}
		env = env->next;
	}
	pipex->path = false;
	return (NULL);
}

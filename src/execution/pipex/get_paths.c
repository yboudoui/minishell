/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:54:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 17:15:53 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	**get_paths(t_list env, t_pipex *pipex)
{
	char	**paths;
	char	*path;
	t_list	tmp;
	t_env_var env_var;

	tmp = env;
	env_var = tmp->content;
	while (tmp)
	{
		env_var = tmp->content;
		if (ft_strncmp(env_var->name, "PATH", 5) == 0)
		{
			path = ft_strdup(env_var->value);
			if (path == NULL)
				return (NULL);
			paths = ft_split(path, ':');
			if (paths == NULL)
				return (NULL);
			free(path);
			pipex->path = true;
			return (paths);
		}
		tmp = tmp->next;
	}
	pipex->path = false;
	return (NULL);
}

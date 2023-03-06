/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:54:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/05 18:22:25 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	**get_paths(t_pipex *pipex)
{
	t_env_var	founded;
	char		**paths;

	if (pipex == NULL)
		return (NULL);
	paths = NULL;
	pipex->path = false;
	founded = env_find("PATH");
	if (founded == NULL)
		return (NULL);
	paths = ft_split(founded->value, ':');
	if (paths == NULL)
		return (NULL);
	pipex->path = true;
	return (paths);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:53:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/07 13:27:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
/*
static inline char	*check_fpath(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (NULL);
	if (is_dir(cmd) != 0)
		return (generic_err(cmd, "Is a directory\n", 2), NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (generic_err(cmd, NULL, 1), NULL);
}
*/
char	*get_cmd_path(t_pipex *pipex, char *cmd)
{
	char	*path;
	int		i;

	if (pipex == NULL)
		return (NULL);
/*
	if (check_fpath(cmd) == NULL)
		return (NULL);
*/
	if (pipex->paths == NULL)
		return (generic_err(cmd, "No such file or directory\n", 2), NULL);
	i = -1;
	path = NULL;
	while (pipex->paths && pipex->paths[++i])
	{
		path = str_join_list((char *[]){
			pipex->paths[i],
			(char *[]){"/", ""}[string_end_with(pipex->paths[i], "/")],
			cmd, NULL});
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	generic_err(cmd, "command not found\n", 2);
	return (NULL);
}

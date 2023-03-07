/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:53:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/07 18:28:21 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static inline char *check_fpath(t_pipex *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		pipex->abs_path_cmd = true;
		if (is_dir(cmd) != 0)
		{
			generic_err(cmd, "Is a directory\n", 2);
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			generic_err(cmd, NULL, 1);
			return (NULL);
		}
	}
	else
		return (NULL);
}

static inline char *check_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (str[i  - 1] == '/')
		str[i - 1] = '\0';
	return (str);
}

char *get_cmd_path(t_pipex *pipex, char *cmd)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	pipex->builtin = is_builtin(cmd);
	if (pipex->builtin)
		return (cmd);
	tmp1 = check_fpath(pipex, cmd);
	if (tmp1 != NULL)
		return (tmp1);
	path_null(pipex, cmd);
	i = 0;
	while (pipex->paths[i])
	{
		check_slash(pipex->paths[i]);
		tmp1 = ft_strjoin(pipex->paths[i], "/");
		null_str_err(tmp1);
		tmp2 = ft_strjoin(tmp1, cmd);
		null_str_err(tmp2);
		free(tmp1);
		if (access(tmp2, F_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	if (!pipex->abs_path_cmd)
		generic_err(cmd, "command not found\n", 2);
	return (NULL);
}

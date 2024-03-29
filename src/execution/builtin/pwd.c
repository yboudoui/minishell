/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:42:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 14:05:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../../inc/minishell.h"

char	*print_working_directory(char *cmd_name)
{
	char	buffer[PATH_MAX];
	char	*working_directory;
	char	*error_msg;

	ft_memset(buffer, 0, PATH_MAX);
	working_directory = getcwd(buffer, PATH_MAX);
	if (working_directory)
		return (ft_strdup(working_directory));
	error_msg = str_join_list((char *[]){cmd_name, ": ",
			"error retrieving the current directory: ",
			"getcwd: cannot access parent directories: ", NULL}, NULL);
	ft_putstr_fd(error_msg, 2);
	free(error_msg);
	return (perror(NULL), ft_strdup(""));
}

int	builtin_pwd(char *argv[])
{
	char	*buffer;

	if (argv == NULL || (*argv) == NULL || string_cmp(*argv, "pwd"))
		return (EXIT_FAILURE);
	buffer = print_working_directory("pwd");
	if (buffer)
	{
		if (ft_putstr_fd(buffer, STDOUT_FILENO) < 0)
		{
			generic_err("pwd: write error", NULL, 1);
			return (free(buffer), 1);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (free(buffer), EXIT_SUCCESS);
}

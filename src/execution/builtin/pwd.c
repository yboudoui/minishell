/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:42:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 11:44:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../../inc/minishell.h"

char	*print_working_directory(char *cmd_name)
{
	char	buffer[PATH_MAX];
	char	*working_directory;

	ft_memset(buffer, 0, PATH_MAX);
	working_directory = getcwd(buffer, PATH_MAX);
	if (working_directory)
		return (ft_strdup(working_directory));
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("error retrieving the current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	perror(NULL);
	return (NULL);
}

int	builtin_pwd(char *argv[])
{
	char	*buffer;

	if (string_cmp(*argv, "pwd"))
		return (EXIT_FAILURE);
	buffer = print_working_directory("pwd");
	if (buffer)
		printf("%s\n", buffer);
	return (free(buffer), EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:42:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 16:06:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../../inc/minishell.h"

int	pwd_err(char *cmd, int system)
{
	if (system == 1)
	{
		ft_putstr_fd("pwd: error retrieving the current directory: ", 2);
		perror(cmd);
	}
	return (-1);
}

int	builtin_pwd(char *argv[])
{
	char	*buffer;
	char	*retval;
	size_t	size;

	(void)argv;
	if (string_cmp(*argv, "pwd"))
		return (EXIT_FAILURE);
	size = 512;
	buffer = NULL;
	while (buffer == NULL)
	{
		free(buffer);
		buffer = ft_calloc(size, sizeof(char));
		if (buffer == NULL)
			return (EXIT_FAILURE);
		retval = getcwd(buffer, size);
		if (retval)
			break ;
		if (retval == NULL)
		{
			pwd_err("getcwd", 1);
			break;
		}
		size *= 2;
		buffer = NULL;
	}
	write(STDIN_FILENO, buffer, ft_strlen(buffer));
	if (retval)
		write(STDIN_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:25:39 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/21 11:01:52 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../../inc/minishell.h"

static int	trailing_newline(char *arg)
{
	if (arg == NULL || *arg != '-')
		return (EXIT_FAILURE);
	while (*(++arg))
		if (*arg != 'n')
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_echo(char *argv[])
{
	bool	new_line;
	size_t	index;

	if (argv == NULL || string_cmp(*argv, "echo"))
		return (EXIT_FAILURE);
	argv += 1;
	index = 0;
	while (!trailing_newline(argv[index]))
		index += 1;
	new_line = (index != 0);
	while (argv[index])
	{
		if (write(STDOUT_FILENO, argv[index], ft_strlen(argv[index])) == -1)
		{
			generic_err("echo: write error", NULL, 1);
			return (1);
		}
		if (argv[index + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		index += 1;
	}
	if (!new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

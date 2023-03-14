/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:25:39 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/14 12:22:53 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		argv[index][ft_strlen(argv[index])] = '\0';
		printf("%s\n", argv[index]);
		/* write(STDIN_FILENO, argv[index], ft_strlen(argv[index])); */
		/* write(STDIN_FILENO, " ", 1); */
		index += 1;
	}
	/* if (!new_line) */
	/* 	write(STDIN_FILENO, "\n", 1); */
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:25:39 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 14:04:53 by yboudoui         ###   ########.fr       */
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
	char	*str;
	size_t	index;

	if (argv == NULL || (*argv) == NULL || string_cmp(*argv, "echo"))
		return (EXIT_FAILURE);
	argv += 1;
	index = 0;
	while (!trailing_newline(argv[index]))
		index += 1;
	new_line = (index != 0);
	str = str_join_list(&argv[index], " ");
	if (!new_line)
		str_merge_to(&str, ft_strdup("\n"));
	if (ft_putstr_fd(str, STDOUT_FILENO) < 0)
	{
		generic_err("echo: write error", NULL, 1);
		return (free(str), 1);
	}
	return (free(str), EXIT_SUCCESS);
}

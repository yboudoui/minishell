/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/16 15:13:27 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	check_error(char **argv)
{
	if (argv[0] && argv[1] && argv[2])
	{
		generic_err(argv[0], "too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	builtin_cd(char *argv[])
{
	if (check_error(argv))
		return (1);
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
		return (EXIT_SUCCESS);
	env_list_insert_new("OLDPWD", my_pwd());
	if (chdir(*argv))
		return (generic_err(*argv, NULL, 1), 1);
	env_list_insert_new("PWD", my_pwd());
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/20 16:14:02 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "../../../inc/minishell.h"

int	builtin_cd(char *argv[])
{
	char	*cdvar;

	cdvar = NULL;
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL || string_cmp(*argv, "~") == 0)
		cdvar = env_get_value("HOME", 0, 0);
	if (argv[0] && argv[1])
		return (generic_err("cd", "too many arguments\n", 2), 1);
	if (cdvar == NULL)
		cdvar = ft_strdup(*argv);
	if (chdir(cdvar) == 0)
	{
		env_list_insert_new("OLDPWD", env_get_value("PWD", 0, 0));
		env_list_insert_new("PWD", print_working_directory("chdir"));
	}
	return (free(cdvar), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/19 19:27:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "../../../inc/minishell.h"

int	check_error(char **argv)
{
	if (argv[0] && argv[1] && argv[2])
	{
		generic_err(argv[0], "too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	check_source(char *cdvar)
{
	chdir(cdvar);
	free(cdvar);
	env_list_insert_new("PWD", print_working_directory("chdir"));
	return (0);
}

int	cd_no_args_or_tilde(void)
{
	char	*reset;
	char	*cdvar;

	cdvar = env_get_value("HOME", 0, 0);
	reset = env_get_value("PWD", 0, 0);
	env_list_insert_new("OLDPWD", ft_strdup(reset));
	free(reset);
	if (cdvar == NULL)
	{
		generic_err("cd", "HOME not set\n", 2);
		return (1);
	}
	check_source(cdvar);
	return (0);
}

int	builtin_cd(char *argv[])
{
	char	*old_pwd;

	old_pwd = NULL;
	if (check_error(argv))
		return (1);
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL || ft_strncmp(*argv, "~", ft_strlen(*argv)) == 0)
		cd_no_args_or_tilde(argv);
	else
		old_pwd = print_working_directory("chdir");
	if (chdir(*argv))
	{
		free(old_pwd);
		return (generic_err(*argv, NULL, 1), 1);
	}
	env_list_insert_new("OLDPWD", old_pwd);
	env_list_insert_new("PWD", print_working_directory("chdir"));
	return (0);
}

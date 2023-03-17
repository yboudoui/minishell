/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 19:23:26 by kdhrif           ###   ########.fr       */
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

int	builtin_cd(char *argv[])
{
	char	*old_pwd;
	char	*reset;
	char	*cdvar;

	if (check_error(argv))
		return (1);
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL || ft_strncmp(*argv, "~", ft_strlen(*argv)) == 0)
	{
		argv = env_get_value("HOME", 0 ,0);
		reset = env_get_value("PWD", 0, 0);
		env_list_insert_new("OLDPWD", ft_strdup(reset));	
		free(reset);
	}
	if (*argv == NULL)
	{
		generic_err("cd", "HOME not set\n", 2);
		return(1);
	}
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


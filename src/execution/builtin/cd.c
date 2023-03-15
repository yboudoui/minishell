/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/15 12:54:39 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	builtin_cd(char *argv[])
{
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

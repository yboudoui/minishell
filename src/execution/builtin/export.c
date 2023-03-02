/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:00:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:25:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
static int	export_set(char *argv[], t_list env)
{
	t_env_var	var;

	if (argv == NULL || env == NULL)
		return (EXIT_FAILURE);
	while (*argv)
	{
		if (**argv == '=')
			printf("export: `%s': not a valid identifier", str);
		else
			environment_list_insert(env, env_var_create(*argv));
		argv += 1;
	}
	return (EXIT_SUCCESS);
}
*/
static void	print_export(void *data)
{
	t_env_var	input;

	input = data;
	if (input == NULL)
		return ;
	printf("export %s=\"%s\"\n", input->name, input->value);
}

int	builtin_export(char *argv[], t_env_list env)
{
//	if (argv == NULL || *argv != "export")
//		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
		return (list_iter((t_list)env, print_export), EXIT_SUCCESS);

	return (1);
//	return (export_set(argv, env));
}

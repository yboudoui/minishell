/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:47:56 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 13:51:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(char *argv[])
{
	t_env_var	var;

	if (argv == NULL || string_cmp(*argv, "unset"))
		return (EXIT_FAILURE);
	argv += 1;
	while (*argv)
	{
		var = env_find(*argv, 0, 0);
		if (var->name)
			env_variable_destroy(var);
		argv += 1;
	}
	return (EXIT_SUCCESS);
}

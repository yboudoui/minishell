/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:36:04 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/08 16:29:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	env_list_singleton(t_env_list list)
{
	static t_env_list	root = NULL;

	if (list != NULL)
		root = (t_env_list)list_first((t_list)list);
	return (root);
}

bool	env_list_create(char *envp[])
{
	t_env_var	var;

	while (*envp)
	{
		var = env_var_create(*envp);
		if (var == NULL)
			return (env_list_destroy(), false);
		env_list_insert(var);
		envp += 1;
	}
	return (true);
}

void	env_list_destroy(void)
{
	t_env_list	env;

	env = env_list_singleton(NULL);
	list_clear(&env, env_variable_destroy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 18:37:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	env_variable_replace(t_env_var *dest, t_env_var src)
{
	if (dest == NULL)
		return ;
	env_variable_destroy(*dest);
	(*dest) = src;
}

void	env_list_insert_new(t_env_list *env, char *name, char *value)
{
	env_list_insert(env, env_variable_create(name, value));
}

t_env_var	env_find(t_env_list env, char *name)
{
	while (env)
	{
		if (!string_cmp(env->var->name, name))
			return (env->var);
		env = env->next;
	}
	return (NULL);
}

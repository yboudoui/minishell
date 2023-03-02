/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:36:04 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:02:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	environment_list_insert(t_env_list *env, t_env_var var)
{
	t_env_list	tmp;
	int			cmp;

	if (env == NULL)
		return ;
	if (*env == NULL)
		return ((void)list_create_back((t_list *)env, var));
	tmp = (*env);
	while (tmp)
	{
		cmp = string_cmp(tmp->var->name, var->name);
		if (cmp == 0)
			return ((void)environment_variable_replace(&tmp->var, var));
		if (cmp < 0)
			return ((void)list_new_insert_before((t_list)tmp, var));
		tmp = tmp->next;
	}
}

t_env_list	environment_list_create(char *envp[])
{
	t_env_list	out;
	t_env_var	var;

	out = NULL;
	while (*envp)
	{
		var = env_var_create(*envp);
		if (var == NULL)
			return (list_clear(&out, environment_variable_destroy), NULL);
		environment_list_insert(&out, var);
		envp += 1;
	}
	return (out);
}

void	environment_list_destroy(void *data)
{
	t_list	input;

	input = data;
	if (data == NULL)
		return ;
	list_clear(&input, environment_variable_destroy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:30:09 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 14:01:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	env_list_insert(t_env_var var)
{
	t_env_list	tmp;
	int			cmp;

	if (var == NULL || var->name == NULL )
		return ;
	tmp = env_list_singleton(NULL);
	while (tmp)
	{
		cmp = string_cmp(var->name, tmp->var->name);
		if (cmp == 0)
			return ((void)env_variable_replace(&tmp->var, var));
		if (cmp < 0)
			return (list_create_prev((t_list *)&tmp, var),
				(void)env_list_singleton(tmp));
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	list_create_back((t_list *)&tmp, var);
	env_list_singleton(tmp);
}

void	env_variable_replace(t_env_var *dest, t_env_var src)
{
	if (dest == NULL)
		return ;
	env_variable_destroy(*dest);
	(*dest) = src;
}

bool	env_list_insert_new(char *name, char *value)
{
	t_env_var	found;

	if (name == NULL)
		return (false);
	if (value == NULL)
		value = ft_strdup("");
	found = env_find(name, 0, ft_strlen(name));
	if (found)
	{
		free(found->value);
		found->value = value;
		return (true);
	}
	env_list_insert(env_variable_create(ft_strdup(name), value));
	return (false);
}

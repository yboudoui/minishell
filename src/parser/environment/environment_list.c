/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:36:04 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 15:56:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_list	environment_list_create(char *envp[])
{
	t_list		out;
	t_env_var	var;

	out = NULL;
	while (*envp)
	{
		var = env_var_create(*envp);
		if (var == NULL)
			return (list_clear(&out, env_var_destroy), NULL);
		list_create_back(&out, var);
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
	list_clear(&input, env_var_destroy);
}

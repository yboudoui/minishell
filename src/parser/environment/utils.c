/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 14:48:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_var	env_find(char *name, size_t start, size_t end)
{
	t_env_list	env;

	if (name == NULL)
		return (NULL);
	env = env_list_singleton(NULL);
	if (start == end)
		end = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->var->name, name + start, end) == 0)
			return (env->var);
		env = env->next;
	}
	return (NULL);
}

void	env_remove(char *name, size_t start, size_t end)
{
	t_env_list	env;

	if (name == NULL)
		return ;
	env = env_list_singleton(NULL);
	if (start == end)
		end = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->var->name, name + start, end) == 0)
			return (list_remove_one((t_list *)&env, env_variable_destroy));
		env = env->next;
	}
}

char	*env_get_value(char *str, size_t start, size_t end)
{
	t_env_var	var;

	var = env_find(str, start, end);
	if (var)
		return (ft_strdup(var->value));
	return (NULL);
}

char	*env_find_and_expand_var(char *str)
{
	char	*output;
	int		idx;
	int		len;

	if (str == NULL)
		return (NULL);
	if (!string_cmp(str, "~"))
		return (env_get_value("HOME", 0, 0));
	idx = -1;
	output = ft_strdup("\0");
	while (str[++idx])
	{
		len = bash_definition_variable(&str[idx]);
		if (len < 0)
			continue ;
		output = str_merge_list((char *[]){
				output, ft_substr(str, 0, idx),
				env_get_value(&str[idx + 1], 0, len), NULL});
		str += (idx + len);
		idx = -1;
	}
	if (ft_strlen(output))
		return (output);
	return (free(output), NULL);
}

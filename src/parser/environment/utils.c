/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/08 16:30:48 by yboudoui         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 13:44:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "minishell.h"

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

char	*env_find_and_expand_var(char *in)
{
	char	*out;
	int		idx;
	int		len;

	if (in == NULL)
		return (NULL);
	idx = 0;
	out = ft_strdup("\0");
	while (in[idx])
	{
		len = bash_definition_variable(&in[idx]);
		idx += 1;
		if (len < 0)
			continue ;
		str_merge_to(&out, ft_substr(in, 0, idx - 1));
		if (in[idx] == '?')
			str_merge_to(&out, ft_itoa(g_global.exit_code));
		else
			str_merge_to(&out, env_get_value(&in[idx], 0, --len));
		in += (idx + len);
		idx = 0;
	}
	if (idx)
		str_merge_to(&out, ft_strdup(in));
	return (out);
}

void	env_find_and_expand_var_to(char **str)
{
	char	*tmp;

	if (str == NULL || (*str) == NULL)
		return ;
	tmp = env_find_and_expand_var(*str);
	if (tmp == NULL)
		return ;
	free(*str);
	(*str) = tmp;
}

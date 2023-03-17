/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 08:48:10 by yboudoui         ###   ########.fr       */
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

void	env_find_and_expand_var(char **str)
{
	char	*output;
	char	*input;
	int		idx;
	int		len;

	if (str == NULL || (*str) == NULL)
		return ;
	input = (*str);
	if (!string_cmp(input, "~"))
	{
		(*str) = env_get_value("HOME", 0, 0);
		return ;
	}
	idx = 0;
	output = ft_strdup("\0");
	while (input[idx])
	{
		len = bash_definition_variable(&input[idx]);
		idx += 1;
		if (len < 0)
			continue ;
		if (input[idx] == '?')
			output = str_merge_list((char *[]){
					output, ft_substr(input, 0, idx - 1),
					ft_itoa(g_global.exit_code), NULL});
		else
			output = str_merge_list((char *[]){
					output, ft_substr(input, 0, idx - 1),
					env_get_value(&input[idx], 0, --len), NULL});
		input += (idx + len);
		idx = 0;
	}
	if (idx)
		output = str_merge_list((char *[]){
				output, ft_strdup(input), NULL});
	free(*str);
	(*str) = output;
}

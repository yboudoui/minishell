/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/07 12:29:36 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	env_list_insert(t_env_var var)
{
	t_env_list	tmp;
	t_env_list	save;
	int			cmp;

	tmp = env_list_singleton(NULL);
	if (var == NULL)
		return ;
	if (tmp == NULL)
		return (list_create_back((t_list *)&tmp, var),
		(void)env_list_singleton(tmp));
	save = tmp;
	while (tmp)
	{
		cmp = string_cmp(var->name, tmp->var->name);
		if (cmp == 0)
			return ((void)env_variable_replace(&tmp->var, var));
		if (cmp < 0)
		{
			list_create_next((t_list *)&tmp, var);
			env_list_singleton((t_env_list)list_first((t_list)tmp));
			return ;
		}
		tmp = tmp->next;
	}
//	tmp = (t_env_list)list_last((t_list)save);
//	list_create_front((t_list *)&tmp, var);
	list_create_front((t_list *)&save, var);
	env_list_singleton(save);
}

void	env_variable_replace(t_env_var *dest, t_env_var src)
{
	if (dest == NULL)
		return ;
	env_variable_destroy(*dest);
	(*dest) = src;
}

void	env_list_insert_new(char *name, char *value)
{
	t_env_var	founded;

	founded = env_find(name, 0, ft_strlen(name));
	if (founded)
	{
		free(founded->value);
		founded->value = value;
		return ;
	}
	env_list_insert(env_variable_create(name, value));
}

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
	return (ft_strdup("\0"));
}

/*
	Warning!!!
	How to handle the the PID of the scrip?
	example:
		echo $$
	source:
		[Advanced Bash-Scripting Guide: Internal Variables]
		(https://tldp.org/LDP/abs/html/internalvariables.html#PROCCID)
*/

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
				output,
				ft_substr(str, 0, idx),
				env_get_value(str, idx, len),
				NULL});
		str += (idx + len);
		idx = -1;
	}
	return (output);
}

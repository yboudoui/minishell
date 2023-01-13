/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:08:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 15:56:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char	*cut_variable_name(char **str)
{
	size_t	size;
	char	*out;

	if (str == NULL || (*str) == NULL)
		return (NULL);
	out = ft_strnstr(*str, "=", ft_strlen(*str));
	if (out == NULL)
		return (NULL);
	size = out - (*str);
	out = ft_substr(*str, 0, size);
	(*str) += size + 1;
	return (out);
}

void	env_var_destroy(void *data)
{
	t_env_var	input;

	input = data;
	if (input == NULL)
		return ;
	free(input->name);
	free(input->value);
	free(input);
}

t_env_var	env_var_create(char *str)
{
	t_env_var	out;

	if (str == NULL)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_env_var));
	if (out == NULL)
		return (NULL);
	out->name = cut_variable_name(&str);
	out->value = ft_strdup(str);
	if (out->name == NULL || out->value == NULL)
		return (env_var_destroy(out), NULL);
	return (out);
}

t_list	env_var_as_path(t_env_var variable)
{
	t_list	out;
	char	**split;

	if (variable == NULL)
		return (NULL);
	split = ft_split(variable->value, ':');
	out = str_array_to_list(split);
	string_array_destroy(split);
	return (out);
}

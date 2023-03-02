/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:08:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:29:36 by yboudoui         ###   ########.fr       */
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

void	environment_variable_destroy(void *data)
{
	t_env_var	input;

	input = data;
	if (input == NULL)
		return ;
	free(input->name);
	free(input->value);
	free(input);
}

t_env_var	environment_variable_create(char *name, char *value)
{
	t_env_var	output;

	if (name == NULL)
		return (NULL);
	output = ft_calloc(1, sizeof(struct s_env_var));
	if (output == NULL)
		return (NULL);
	(*output) = (struct s_env_var){name, value};
	return (output);
}

void	environment_variable_replace(t_env_var *dest, t_env_var src)
{
	if (dest == NULL)
		return ;
	environment_variable_destroy(*dest);
	(*dest) = src;
}

t_env_var	env_var_create(char *str)
{
	char	*name;
	char	*value;
	t_env_var	output;

	if (str == NULL)
		return (NULL);
	name = cut_variable_name(&str);
	if (name == NULL)
		return (NULL);
	value = ft_strdup(str);
	output = environment_variable_create(name, value);
	if (output)
		return (output);
	return (environment_variable_destroy(output), NULL);
}

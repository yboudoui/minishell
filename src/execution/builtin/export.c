/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:00:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 18:59:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_valid_bash_name(char c)
{
	return (is_alnum(c) || c == '_');
}

// not well written
static int	parse_export_arg(char *arg, t_env_list *env)
{
	char		*name;
	char		*value;
	size_t		len;
	t_env_var	var;

	len = 0;
	while (is_valid_bash_name(arg[len]) && arg[len])
		len += 1;
	value = NULL;
	name = ft_substr(arg, 0, len);
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(&arg[len], "=", 1))
	{
		value = ft_substr(arg, len + 1, ft_strlen(arg));
		env_list_insert_new(env, name, value);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(&arg[len], "+=", 2))
	{
		value = ft_substr(arg, len + 2, ft_strlen(arg));
		var = env_find(*env, name);
		if (var)
			var->value = str_merge_list((char *[]){var->value, value, NULL});
		else
			env_list_insert_new(env, name, value);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void	print_export(void *data)
{
	t_env_var	input;

	input = data;
	if (input == NULL || input->name == NULL)
		return ;
	printf("export %s=\"%s\"\n", input->name, input->value);
}

int	builtin_export(char *argv[], t_env_list *env)
{
	if (argv == NULL || env == NULL || string_cmp(*argv, "export"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
		return (list_iter((t_list)env, print_export), EXIT_SUCCESS);
	while (*argv)
	{
		if (parse_export_arg(*argv, env))
			printf("export: `%s': not a valid identifier", *argv);
		argv += 1;
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:00:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/20 14:12:36 by kdhrif           ###   ########.fr       */
/*   Updated: 2023/03/19 19:07:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include "builtin.h"

static char	*extract_variable_name(char **arg)
{
	int		len;
	char	*out;

	len = bash_definition_name(*arg);
	if (len < 0)
		return (NULL);
	out = ft_substr(*arg, 0, len);
	if (out)
		(*arg) += len;
	return (out);
}

static bool	parse_export_arg(char *arg)
{
	char		*name;
	char		*value;
	t_env_var	var;

	if (arg == NULL || is_digit(*arg))
		return (false);
	name = extract_variable_name(&arg);
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(arg, "=", 1) == 0)
	{
		value = ft_substr(arg, 1, ft_strlen(arg));
		if (value && env_list_insert_new(name, value))
			free(name);
		return (true);
	}
	else if (ft_strncmp(arg, "+=", 2) == 0)
	{
		value = ft_substr(arg, 2, ft_strlen(arg));
		var = env_find(name, 0, 0);
		if (var)
			str_merge_to(&var->value, value);
		else if (env_list_insert_new(name, value))
			free(name);
		return (true);
	}
	return (free(name), false);
}

static void	print_export(void *data, void *_)
{
	t_env_var	input;

	(void)_;
	input = data;
	if (input == NULL || input->name == NULL)
		return ;
	printf("export %s=\"%s\"\n", input->name, input->value);
}

int	builtin_export(char *argv[])
{
	t_env_list	env;

	env = env_list_singleton(NULL);
	if (argv == NULL || env == NULL || string_cmp(*argv, "export"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
		return (list_iter(env, print_export, NULL), EXIT_SUCCESS);
	while (*argv)
	{
		if (parse_export_arg(*argv) == false)
			printf("export: `%s': not a valid identifier\n", *argv);
		argv += 1;
	}
	return (EXIT_SUCCESS);
}

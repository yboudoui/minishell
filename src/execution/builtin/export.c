/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:00:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/15 17:52:43 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

// not well written
static int	parse_export_arg(char *arg)
{
	char		*name;
	char		*value;
	int			len;
	t_env_var	var;

	len = bash_definition_name(arg);
	if (len < 0)
		return (EXIT_FAILURE);
	name = ft_substr(arg, 0, len);
	if (name == NULL)
		return (EXIT_FAILURE);
	value = NULL;
	if (!ft_strncmp(&arg[len], "=", 1))
	{
		value = ft_substr(arg, len + 1, ft_strlen(arg));
		env_list_insert_new(name, value);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(&arg[len], "+=", 2))
	{
		value = ft_substr(arg, len + 2, ft_strlen(arg));
		var = env_find(name, 0, 0);
		if (var)
			var->value = str_merge_list((char *[]){var->value, value, NULL});
		else
			env_list_insert_new(name, value);
		return (EXIT_SUCCESS);
	}
	return (free(name), EXIT_FAILURE);
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
		if (parse_export_arg(*argv))
			printf("export: `%s': not a valid identifier\n", *argv);
		argv += 1;
	}
	return (EXIT_SUCCESS);
}

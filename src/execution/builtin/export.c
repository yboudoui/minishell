/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:00:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 14:08:32 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include "builtin.h"

static char	*extract_variable_name(char **arg)
{
	int		len;
	char	*out;

	if (arg == NULL || (*arg) == NULL || is_digit(**arg))
		return (NULL);
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

	name = extract_variable_name(&arg);
	if (name == NULL)
		return (false);
	if (ft_strncmp(arg, "=", 1) == 0)
	{
		value = ft_substr(arg, 1, ft_strlen(arg));
		env_list_insert_new(name, value);
		return (free(name), true);
	}
	else if (ft_strncmp(arg, "+=", 2) == 0)
	{
		value = ft_substr(arg, 2, ft_strlen(arg));
		var = env_find(name, 0, 0);
		if (var)
			str_merge_to(&var->value, value);
		else
			env_list_insert_new(name, value);
		return (free(name), true);
	}
	return (free(name), true);
}

static void	print_export(void *data, void *str)
{
	t_env_var	input;
	char		*line;
	char		**fmt;

	input = data;
	if (input == NULL || input->name == NULL)
		return ;
	fmt = (char *[]){
		"export ", input->name, "=\"", input->value, "\"\n", NULL};
	line = str_join_list(fmt, NULL);
	str_merge_to(str, line);
}

int	builtin_export(char *argv[])
{
	char		*str;

	if (argv == NULL || (*argv) == NULL || string_cmp(*argv, "export"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
	{
		str = ft_strdup("");
		list_iter(env_list_singleton(NULL), print_export, &str);
		if (ft_putstr_fd(str, STDOUT_FILENO) < 0)
			ft_putstr_fd("minishell: "
				"export: write error: No space left on device\n",
				STDERR_FILENO);
		return (free(str), EXIT_SUCCESS);
	}
	while (*argv)
	{
		if (parse_export_arg(*argv) == false)
			printf("minishell: export: `%s': not a valid identifier\n", *argv);
		argv += 1;
		return (1);
	}
	return (EXIT_SUCCESS);
}

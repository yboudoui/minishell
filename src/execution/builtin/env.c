/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:56:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 15:05:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static void	print_env(void *data, void *str)
{
	t_env_var	input;
	char		*line;
	char		**fmt;

	input = data;
	if (input == NULL || input->name == NULL || input->value == NULL)
		return ;
	fmt = (char *[]){input->name, "=", input->value, "\n", NULL};
	line = str_join_list(fmt, NULL);
	str_merge_to(str, line);
}

int	builtin_env(char *argv[])
{
	char		**fmt;
	char		*str;

	if (argv == NULL || (*argv) == NULL || string_cmp(*argv, "env"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv != NULL)
	{
		fmt = (char *[]){
			"env: ‘", *argv, "’: No such file or directory\n", NULL};
		str = str_join_list(fmt, NULL);
		ft_putstr_fd(str, STDERR_FILENO);
		g_global.exit_code = 127;
		return (free(str), 127);
	}
	str = ft_strdup("");
	list_iter(env_list_singleton(NULL), print_env, &str);
	if (ft_putstr_fd(str, STDOUT_FILENO) < 0)
	{
		generic_err("env: write error", NULL, 1);
		return (free(str), 1);
	}
	return (free(str), EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:56:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/21 07:05:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_env(void *data, void *_)
{
	t_env_var	input;

	(void)_;
	input = data;
	if (input == NULL || input->name == NULL)
		return ;
	printf("%s=%s\n", input->name, input->value);
}

int	builtin_env(char *argv[])
{
	t_env_list	env;

	env = env_list_singleton(NULL);
	if (argv == NULL || env == NULL || string_cmp(*argv, "env"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv != NULL)
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	return (list_iter((t_list)env, print_env, NULL), EXIT_SUCCESS);
}

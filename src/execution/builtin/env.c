/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:56:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 19:28:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_env(void *data)
{
	t_env_var	input;

	input = data;
	if (input == NULL || input->name == NULL)
		return ;
	printf("%s=%s\n", input->name, input->value);
}

int	builtin_env(char *argv[], t_env_list *env)
{
	if (argv == NULL || env == NULL || string_cmp(*argv, "env"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
		return (list_iter((t_list)*env, print_env), EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

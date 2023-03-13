/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:59:20 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/13 16:45:19 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../../inc/minishell.h"

int	builtin_exit(char *argv[])
{
	int	exit_code;

	exit_code = 0;
	argv += 1;
	if (*argv != NULL)
	{
		/// check letter
		exit_code = ft_atoi(argv[0]);
		if (exit_code > 0)
			exit_code %= 256;
		else
		{
			exit_code *= -1;
			exit_code %= 256;
			exit_code = 256 - exit_code;
		}
	}
	printf("exit\n");
	printf("%d\n", exit_code);
	meta_exit(exit_code, NULL);
	return (EXIT_SUCCESS);
}

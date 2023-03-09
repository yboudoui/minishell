/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:47:56 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 14:48:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(char *argv[])
{
	if (argv == NULL || string_cmp(*argv, "unset"))
		return (EXIT_FAILURE);
	argv += 1;
	while (*argv)
	{
		env_remove(*argv, 0, 0);
		argv += 1;
	}
	return (EXIT_SUCCESS);
}

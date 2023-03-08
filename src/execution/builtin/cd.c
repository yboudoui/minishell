/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/08 16:54:41 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(char *argv[])
{
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (string_cmp(argv[0], "~") == 0)
		argv[0] = env_get_value("HOME", 0, 0);
	if (chdir(*argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

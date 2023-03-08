/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/08 17:35:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(char *argv[])
{
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv != NULL && chdir(*argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

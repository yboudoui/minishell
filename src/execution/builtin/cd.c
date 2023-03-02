/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:21:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd(char *argv[])
{
//	if (argv == NULL || *argv != "cd")
//		return (EXIT_FAILURE);
	argv += 1;
	if (chdir(*argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

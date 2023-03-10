/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:52:52 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/10 18:51:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	builtin_cd(char *argv[])
{
	if (argv == NULL || string_cmp(*argv, "cd"))
		return (EXIT_FAILURE);
	argv += 1;
	if (*argv == NULL)
		return (EXIT_SUCCESS);
	if (chdir(*argv))
		return (generic_err(*argv, NULL, 1), 1);
	return (0);
}

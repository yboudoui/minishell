/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:16:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 14:03:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

typedef struct s_builtin_match {
	char			*name;
	t_fp_builtin	func;
}	t_builtin_match;

static const t_builtin_match	g_builtin_mathc[7] = {
{"cd", builtin_cd},
{"pwd", builtin_pwd},
{"env", builtin_env},
{"exit", builtin_exit},
{"echo", builtin_echo},
{"unset", builtin_unset},
{"export", builtin_export},
};

t_fp_builtin	is_builtin(char *argv)
{
	size_t	index;

	if (argv == NULL)
		return (NULL);
	index = 0;
	while (index < 7)
	{
		if (!string_cmp(argv, g_builtin_mathc[index].name))
			return (g_builtin_mathc[index].func);
		index += 1;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:07:49 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/06 11:40:38 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	*parse_env_var(void *data)
{
	t_env_var	env;
	char		*equal;

	env = data;
	if (env == NULL)
		return (NULL);
	equal = ft_strdup("=");
	return (str_merge_list((char *[]){
			env->name, equal, env->value, NULL
		}));
}

char	**parse_env(void)
{
	return (list_to_array((t_list)env_list_singleton(NULL), parse_env_var));
}

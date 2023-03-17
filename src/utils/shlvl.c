/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:34:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/17 07:44:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	incr_shlvl(void)
{
	char	*shlvl;
	int		shl;

	shlvl = env_get_value("SHLVL", 0, 0);
	shl = ft_atoi(shlvl);
	shl += 1;
	free(shlvl);
	shlvl = ft_itoa(shl);
	env_list_insert_new("SHLVL", shlvl);
}

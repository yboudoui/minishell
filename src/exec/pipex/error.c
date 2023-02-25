/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:55:39 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/25 17:11:30 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	generic_err(char *str, int system)
{
	char	*s;

	if (system == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(str);
	}
}

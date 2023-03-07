/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:55:39 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/07 14:44:08 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	generic_err(char *cmd, char *error, int system)
{
	if (system == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
	}
	if (system == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error, 2);
	}
	return (-1);
}

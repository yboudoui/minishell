/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:55:39 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/21 14:54:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	generic_err(char *cmd, char *error, int system)
{
	char	**warning;
	char	*str;

	if (system == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
	}
	if (system == 2)
	{
		warning = (char *[]){"minishell: ", cmd, ": ", error, NULL};
		str = str_join_list(warning, NULL);
		ft_putstr_fd(str, 2);
		free(str);
	}
	return (-1);
}

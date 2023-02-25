/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:37:42 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/25 16:38:00 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	f_open(char *file, int flag, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flag);
	else
		fd = open(file, flag, mode);
	if (fd == -1)
		perror(file);
	return (fd);
}

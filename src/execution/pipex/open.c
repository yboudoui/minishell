/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:37:42 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/11 16:19:52 by kdhrif           ###   ########.fr       */
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
		generic_err(file, NULL, 1);
	return (fd);
}

int	close_fd(int *fd)
{
	if ((*fd) < 2)
		return (0);
	/* printf("closing fd %d\n", *fd); */
	if (close(*fd) == -1)
		return (generic_err("close", NULL, 1));
	else
		*fd = -1;
	return (0);
}

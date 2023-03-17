/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:37:42 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/17 18:34:18 by yboudoui         ###   ########.fr       */
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
	struct stat	buf;

	if (fstat(*fd, &buf) != -1)
		close(*fd);
	(*fd) = -1;
	return (0);
}

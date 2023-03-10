/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/11 11:00:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	dup_fd(int fd, int new_fd)
{
	if (dup2(fd, new_fd) == -1)
		return (generic_err("Dup2", NULL, 1));
	return (0);
}

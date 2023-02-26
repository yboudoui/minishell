/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/25 19:57:11 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	dup_fd(int fd, int new_fd)
{
	if (dup2(*fd, *new_fd) == -1)
		generic_err("Dup2", 1);
}
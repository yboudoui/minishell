/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:02:12 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/21 16:31:26 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (0);
	return (write(fd, s, ft_strlen(s)));
}

ssize_t	ft_putnl_fd(char *s, int fd)
{
	size_t	size;

	if (!s)
		return (0);
	size = write(fd, s, ft_strlen(s));
	size += write(fd, "\n", 1);
	return (size);
}

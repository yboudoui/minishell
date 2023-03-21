/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:01:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/21 16:13:59 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

ssize_t	ft_putchar_fd(char c, int fd)
{
	ssize_t	ret;

	ret = write(fd, &c, 1);
	if (ret == -1)
		return (generic_err("write error", NULL, 1));
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_find_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:50:56 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/29 17:44:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	ft_str_find_prefix(char *str, char *prefix)
{
	size_t	len;

	len = ft_strlen(prefix);
	if (len && ft_strncmp(str, prefix, len) == 0)
		return (len);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_slice_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:20:14 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/29 18:11:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_slice_prefix(char *str, char *prefix)
{
	size_t	len;

	len = ft_str_find_prefix(str, prefix);
	if (len)
		return (ft_substr(str, 0, len));
	return (NULL);
}

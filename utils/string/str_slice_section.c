/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_slice_section.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:08:39 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/29 17:49:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_slice_section(char *str, char *start, char *end)
{
	size_t	len;
	char	*tmp;

	len = ft_str_find_prefix(str, start);
	if (len == 0)
		return (NULL);
	tmp = ft_strnstr(&str[len], end, ft_strlen(&str[len]));
	if (!tmp)
		return (NULL);
	len = (tmp + ft_strlen(end)) - str;
	return (ft_substr(str, 0, len));

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_slice_section.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:08:39 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/14 14:52:59 by yboudoui         ###   ########.fr       */
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

int	str_must_slice_section(char *str, char **section, char **out)
{
	size_t	len;
	char	*tmp;

	len = ft_str_find_prefix(str, section[0]);
	if (len == 0)
		return (0);
	tmp = ft_strnstr(&str[len], section[1], ft_strlen(&str[len]));
	if (!tmp)
		return (-1);
	len = (tmp + ft_strlen(section[1])) - str;
	(*out) = ft_substr(str, 0, len);
	return (1);
}

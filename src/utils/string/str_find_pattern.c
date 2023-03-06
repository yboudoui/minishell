/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_find_pattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:28:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 15:58:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_find_pattern(const char *str, char *(*pattern)(const char *))
{
	char	*output;

	if (str == NULL || pattern == NULL)
		return (NULL);
	while (*str)
	{
		output = pattern(str);
		if (output)
			return (output);
		str += 1;
	}
	return (NULL);
}

t_list	str_find_all_pattern(const char *str, char *(*pattern)(const char *))
{
	t_list	output;
	char	*pattern_founded;

	if (str == NULL || pattern == NULL)
		return (NULL);
	output = NULL;
	while (*str)
	{
		pattern_founded = pattern(str);
		if (pattern_founded == NULL)
			str += 1;
		else
		{
			list_create_back(&output, pattern_founded);
			str += ft_strlen(pattern_founded);
		}
	}
	return (output);
}

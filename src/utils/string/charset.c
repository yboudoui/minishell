/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:28:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 10:41:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static char	*g_charset;

static bool	charset_fp(int c)
{
	size_t	index;

	index = 0;
	while (g_charset[index])
	{
		if (g_charset[index] == c)
			return (true);
		index += 1;
	}
	return (false);
}

t_fp_charset	str_charset(char *str)
{
	if (str == NULL)
		return (NULL);
	g_charset = str;
	return (charset_fp);
}

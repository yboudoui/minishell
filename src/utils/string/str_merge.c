/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:17:40 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 08:15:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_merge(char *str, ...)
{
	char	*out;
	char	*tmp;
	char	*current;
	va_list	arg;

	va_start(arg, str);
	out = str;
	while (1)
	{
		current = va_arg (arg, char*);
		if (!current)
			break ;
		tmp = out;
		out = ft_strjoin(tmp, current);
		free(tmp);
		free(current);
	}
	va_end(arg);
	return (out);
}

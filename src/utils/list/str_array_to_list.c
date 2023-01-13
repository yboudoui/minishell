/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:18:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 08:57:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "list.h"

t_list	str_array_to_list(char *str_array[])
{
	t_list	out;

	out = NULL;
	while (*str_array)
	{
		list_create_back(&out, ft_strdup(*str_array));
		str_array += 1;
	}
	return (out);
}

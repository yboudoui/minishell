/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:02:55 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/08 14:03:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

size_t	sizeof_array(void *ptr, size_t sizeof_type, void *sentinel)
{
	size_t	index;

	if (ptr == NULL || sizeof_type == 0)
		return (0);
	index = 0;
	while (ft_memcmp(ptr, sentinel, sizeof_type))
	{
		index += 1;
		ptr += (index * sizeof_type);
	}
	return (index);
}

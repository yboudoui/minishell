/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:57:56 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 10:19:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strdup(const char *s)
{
	char	*output;
	size_t	index;

	index = ft_strlen(s) + 1;
	output = ft_calloc(index, sizeof(char));
	if (output)
		ft_memcpy(output, s, index);
	return (output);
}

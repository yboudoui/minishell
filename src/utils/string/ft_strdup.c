/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:57:56 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 13:10:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strdup(const char *s)
{
	char	*output;
	size_t	index;

	if (s == NULL)
		return (NULL);
	index = ft_strlen(s) + 1;
	output = ft_calloc(index, sizeof(char));
	if (output)
		ft_memcpy(output, s, index);
	return (output);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:47:34 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 08:15:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	s1len;
	size_t	s2len;

	if (!s1 | !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	output = ft_calloc(s1len + s2len + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_memcpy(output, s1, s1len);
	ft_memcpy(&output[s1len], s2, s2len);
	return (output);
}

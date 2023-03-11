/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:48:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/07 10:42:23 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	end;

	end = ft_strlen(s);
	while (end && s[end] != (char)c)
		end--;
	if (s[end] == (char)c)
		return ((char *)&s[end]);
	return (NULL);
}

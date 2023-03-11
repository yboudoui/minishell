/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:25:23 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:06:44 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*l_tmp;
	char	*b_tmp;
	int		len_tmp;

	if (!*little)
		return ((char *)big);
	while (*big && len)
	{
		len_tmp = len;
		b_tmp = (char *)big;
		l_tmp = (char *)little;
		while ((*b_tmp++ == *l_tmp++) && len_tmp--)
			if (!*l_tmp)
				return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

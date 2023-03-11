/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:09:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 16:29:25 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_itoa(int n)
{
	char		*out;
	int			size;
	long int	m;
	long int	ntmp1;
	long int	ntmp2;

	m = n;
	size = (m <= 0);
	ntmp1 = m * ((m >= 0) - (m < 0));
	while (ntmp1 > 0)
	{
		ntmp1 /= 10;
		size++;
	}
	out = ft_calloc(size + 1, sizeof(char));
	if (!out)
		return (NULL);
	out[0] = '-';
	ntmp2 = m * ((m >= 0) - (m < 0));
	while (--size >= (m < 0))
	{
		out[size] = '0' + (ntmp2 % 10);
		ntmp2 /= 10;
	}
	return (out);
}

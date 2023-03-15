/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:09:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/15 16:12:38 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_itoa(long long int n)
{
	char		*out;
	int			size;
	long long int	m;
	long long int	ntmp1;
	long long int	ntmp2;

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

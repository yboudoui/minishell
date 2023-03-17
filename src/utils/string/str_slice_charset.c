/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_slice_charset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:28:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 10:34:38 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_slice_charset(char *str, t_fp_charset charset)
{
	size_t	index;

	index = 0;
	while (str[index] && charset(str[index]))
		index++;
	if (index == 0)
		return (NULL);
	return (ft_substr(str, 0, index));
}

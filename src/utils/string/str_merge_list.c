/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_merge_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:03:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/23 15:15:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_merge_list(char *str[])
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	while (*str)
	{
		tmp = output;
		output = ft_strjoin(tmp, *str);
		free(tmp);
		free(*str);
		(*str) = NULL;
		str += 1;
	}
	return (output);
}

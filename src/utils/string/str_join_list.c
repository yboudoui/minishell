/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:06:57 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/23 15:26:22 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_join_list(char *str[])
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	while (*str)
	{
		tmp = output;
		output = ft_strjoin(tmp, *str);
		free(tmp);
		str += 1;
	}
	return (output);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:06:57 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/21 14:30:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_join_list(char *str[], char *delimiter)
{
	size_t	index;
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	index = 0;
	while (str[index])
	{
		tmp = output;
		output = ft_strjoin(tmp, str[index]);
		free(tmp);
		if (delimiter && str[index + 1])
		{
			tmp = output;
			output = ft_strjoin(tmp, delimiter);
			free(tmp);
		}
		index += 1;
	}
	return (output);
}

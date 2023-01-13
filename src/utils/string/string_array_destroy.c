/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:29:34 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 08:31:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	string_array_destroy(void *data)
{
	char	**input;
	size_t	index;

	if (data == NULL)
		return ;
	index = 0;
	input = data;
	while (input[index])
	{
		free(input[index]);
		index++;
	}
	free(data);
}

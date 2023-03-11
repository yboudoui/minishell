/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:07:14 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/26 18:15:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

bool	is_empty(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!is_space(*str))
			return (false);
		str += 1;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:46:53 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/28 17:01:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"
#include "string.h"

t_token	token_is_spaces(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] && is_space(str[index]))
		index++;
	if (index == 0)
		return (NULL);
	return (token_create(TOKEN_SPACES, ft_strdup(" ")));
}

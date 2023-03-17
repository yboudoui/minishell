/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_merge_list_to.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:43:43 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 13:21:59 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	str_merge_to(char **str, char *s)
{
	char	*tmp;

	if (str == NULL)
		return ;
	if (s)
	{
		tmp = ft_strjoin((*str), s);
		free(s);
		free(*str);
		(*str) = tmp;
	}
}

void	str_merge_list_to(char **str, char *list[])
{
	if (str == NULL || list == NULL)
		return ;
	str_merge_to(str, str_merge_list(list));
}

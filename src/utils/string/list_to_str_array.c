/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:24:08 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 08:38:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "list.h"

char	**list_to_str_array(t_list lst, bool (*cast_content)(void *, char **))
{
	size_t	size;
	size_t	index;
	char	**out;

	size = list_size(lst);
	if (!size)
		return (NULL);
	out = ft_calloc(size + 1, sizeof(char *));
	if (!out)
		return (NULL);
	index = 0;
	while (index < size)
	{
		if (!cast_content(lst->content, &out[index]))
			return (string_array_destroy(out), NULL);
		lst = lst->next;
		index++;
	}
	return (out);
}

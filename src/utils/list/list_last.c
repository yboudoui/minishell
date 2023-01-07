/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:26:40 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/07 14:01:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	list_last(t_list lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

size_t	list_size(t_list lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		size += 1;
		lst = lst->next;
	}
	return (size);
}

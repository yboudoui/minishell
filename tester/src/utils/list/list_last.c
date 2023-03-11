/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:26:40 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 15:31:45 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	list_last(t_list lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	list_first(t_list lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
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

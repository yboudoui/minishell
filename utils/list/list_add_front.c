/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:33:10 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/22 15:59:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool	list_add_front(t_list *lst, t_list new)
{
	if (lst == NULL || (*lst) == NULL || new == NULL)
		return (false);
	new->next = (*lst);
	new->next->prev = new;
	(*lst) = new;
	return (true);
}

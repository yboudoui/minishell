/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:47:55 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 14:17:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool	list_add_front(t_list *lst, t_list new)
{
	if (lst == NULL || new == NULL)
		return (false);
	new->next = (*lst);
	new->next->prev = new;
	(*lst) = new;
	return (true);
}

bool	list_add_back(t_list *root, t_list new)
{
	t_list	tmp;

	if (!root || !new)
		return (false);
	tmp = (*root);
	if (tmp)
	{
		tmp = list_last(*root);
		tmp->next = new;
		new->prev = tmp;
	}
	else
		(*root) = new;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:47:55 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 17:58:32 by yboudoui         ###   ########.fr       */
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

	if (root == NULL || new == NULL)
		return (false);
	tmp = (*root);
	if (tmp)
		list_last(tmp)->next = new;
	else if (root)
		(*root) = new;
	return (true);
}

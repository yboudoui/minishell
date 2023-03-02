/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:18:25 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 15:56:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_new_insert_before(t_list root, void *data)
{
	t_list	new;

	if (root == NULL)
		return ;
	new = list_create(data);
	if (new == NULL)
		return ;
	new->next = root->next;
	new->prev = root;
	root->next = new;
	if (new->next)
		new->next->prev = new;
}

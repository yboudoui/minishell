/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:45:01 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:46:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_remove_one(t_list *root, void (*del)(void*))
{
	t_list	new;

	if (!root || !(*root))
		return ;
	new = (*root)->next;
	list_destroy(*root, del);
	(*root) = new;
}

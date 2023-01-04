/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:41:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 19:00:56 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_destroy(t_list lst, t_fp_destroy_content del)
{
	if (!lst || !del)
		return ;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->prev)
		lst->prev->next = lst->next;
	del(lst->content);
	(*lst) = (struct s_list){};
	free(lst);
}

void	list_remove_one(t_list *root, t_fp_destroy_content del)
{
	t_list	current;

	if (!root || !del)
		return ;
	current = (*root);
	if (current == NULL)
		return ;
	(*root) = (*root)->next;
	list_destroy(current, del);
	current = NULL;
}

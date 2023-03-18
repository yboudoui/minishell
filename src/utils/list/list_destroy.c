/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:41:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/18 19:48:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_destroy(t_list lst, t_fp_destroy_content del)
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

void	list_remove_one(void *lst, t_fp_destroy_content del)
{
	t_list	*current;
	t_list	new;

	current = lst;
	if (current == NULL || (*current) == NULL)
		return ;
	new = (*current)->next;
	if ((*current)->next)
		(*current)->next->prev = (*current)->prev;
	if ((*current)->prev)
		(*current)->prev->next = (*current)->next;
	list_destroy(*current, del);
	(*current) = new;
}

void	list_clear(void *root, t_fp_destroy_content del)
{
	t_list	tmp;
	t_list	*lst;

	lst = root;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		list_destroy(*lst, del);
		(*lst) = tmp;
	}
}

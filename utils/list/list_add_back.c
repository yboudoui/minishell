/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:38:26 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/25 14:35:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool	list_add_back(t_list *lst, t_list new)
{
	t_list	tmp;

	if (lst == NULL || new == NULL)
		return (false);
	tmp = (*lst);
	if (tmp)
		list_last(tmp)->next = new;
	else if (lst)
		(*lst) = new;
	return (true);
}

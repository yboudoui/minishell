/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:47:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:50:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	list_clear(t_list *lst, t_fp_destroy_content del)
{
	t_list	tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		list_destroy(*lst, del);
		(*lst) = tmp;
	}
}

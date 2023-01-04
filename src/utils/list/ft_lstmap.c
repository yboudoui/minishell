/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:47:02 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:50:47 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	ft_lstmap(t_list lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	output;
	t_list	tmp;

	output = NULL;
	while (lst)
	{
		tmp = list_create(f(lst->content));
		if (tmp)
			list_add_back(&output, tmp);
		else
		{
			list_clear(&output, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (output);
}

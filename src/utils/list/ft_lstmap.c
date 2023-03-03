/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:47:02 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/03 15:57:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_iter(t_list lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

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
			return (list_clear(&output, del), NULL);
		lst = lst->next;
	}
	return (output);
}

void	*list_to_array(t_list lst, void *(*f)(void *))
{
	size_t	index;
	size_t	size;
	void	**out;

	if (lst == NULL)
		return (NULL);
	size = list_size(lst);
	out = ft_calloc(size + 1, sizeof(void *));
	index = 0;
	while (lst)
	{
		out[index] = f(lst->content);
		index += 1;
		lst = lst->next;
	}
	return (out);
}

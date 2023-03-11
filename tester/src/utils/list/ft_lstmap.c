/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:47:02 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 14:27:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_iter(void *list, void (*f)(void *, void *), void *data)
{
	t_list	lst;

	lst = list;
	while (lst)
	{
		f(lst->content, data);
		lst = lst->next;
	}
}

t_list	ft_lstmap(t_list lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	output;

	output = NULL;
	while (lst)
	{
		if (!list_create_back(&output, f(lst->content)))
			return (list_clear(&output, del), NULL);
		lst = lst->next;
	}
	return (output);
}

void	*list_subset(void *list, void *(*f)(void *))
{
	t_list	lst;
	t_list	output;
	void	*tmp;

	lst = list;
	output = NULL;
	while (lst)
	{
		tmp = f(&lst);
		if (tmp != NULL)
			list_create_back(&output, tmp);
		if (lst != NULL)
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

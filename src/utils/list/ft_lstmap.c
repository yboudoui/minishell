/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:47:02 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 16:15:27 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "../../../inc/minishell.h"

void	ft_lstiter(t_list lst, void (*f)(void *))
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

int	ft_lstsize(t_list lst)
{
	int	out;

	out = 0;
	while (lst)
	{
		out += 1;
		lst = lst->next;
	}
	return (out);
}

void	*list_to_array(t_list lst, void *(*f)(void *))
{
	size_t	index;
	size_t	size;
	void	**out;

	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst);
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

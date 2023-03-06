/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:30:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 15:59:31 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	list_create(void *content)
{
	t_list	output;

	output = ft_calloc(1, sizeof(struct s_list));
	if (output != NULL)
		output->content = content;
	return (output);
}

bool	list_create_back(t_list *root, void *content)
{
	return (list_add_back(root, list_create(content)));
}

bool	list_create_front(t_list *root, void *content)
{
	return (list_add_front(root, list_create(content)));
}

bool	list_create_next(t_list *root, void *content)
{
	return (list_add_next(root, list_create(content)));
}

bool	list_create_prev(t_list *root, void *content)
{
	return (list_add_prev(root, list_create(content)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:30:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 17:56:45 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	list_create(void *content)
{
	t_list	output;

	output = ft_calloc(1, sizeof(struct s_list));
	if (output != NULL)
		(*output) = (struct s_list){.content = content};
	return (output);
}

bool	list_create_back(t_list *root, void *content)
{
	return (list_add_back(root, list_create(content)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:30:47 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:24:21 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	list_create(void *content)
{
	t_list	output;

	output = ft_calloc(1, sizeof(struct s_list));
	if (NULL != output)
		output->content = content;
	return (output);
}

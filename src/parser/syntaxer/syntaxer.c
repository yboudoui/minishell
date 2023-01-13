/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:47:18 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 15:54:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntaxer.h"

static t_list	slice_commande(t_list *lst)
{
	t_token	token;
	t_list	output;

	output = NULL;
	while (*lst)
	{
		token = (*lst)->content;
		if (token->type == TOKEN_PIPE)
			break ;
		else
			list_create_back(&output, token_dup(token));
		(*lst) = (*lst)->next;
	}
	return (output);
}

bool	syntaxer(t_list *root)
{
	t_list	output;
	t_list	lst;
	t_token	token;

	output = NULL;
	lst = (*root);
	while (lst)
	{
		token = lst->content;
		if (token->type == TOKEN_PIPE)
			lst = lst->next;
		else
			list_create_back(&output, commande_create(slice_commande(&lst)));
	}
	list_clear(root, token_destroy);
	(*root) = output;
	return (true);
}

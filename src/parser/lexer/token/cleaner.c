/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:16:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/07 14:55:17 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	token_list_sanitizer(t_list *root)
{
	t_token	token;
	t_list	output;
	t_list	lst;

	output = NULL;
	lst = (*root);
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (false);
		if (token->type != TOKEN_SPACES)
			list_create_back(&output, token_dup(token));
		lst = lst->next;
	}
	list_clear(root, token_destroy);
	(*root) = output;
	return (true);
}

bool	token_list_merging(t_list *root)
{
	t_token	token;
	t_list	output;
	t_list	lst;

	output = NULL;
	lst = (*root);
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (false);
		if (token->type != TOKEN_SPACES)
			list_create_back(&output, token_dup(token));
		lst = lst->next;
	}
	list_clear(root, token_destroy);
	(*root) = output;
	return (true);
}

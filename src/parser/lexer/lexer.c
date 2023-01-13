/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:58:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 15:55:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include "show.h"

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

char	*lexer(char *input, t_list *out)
{
	char	*error;

	error = tokenizer(input, out);
	if (error)
		return (error);
	print_colored_token_list("~$ ", *out);
	token_list_sanitizer(out);
	print_colored_token_list("~$ ", *out);
	return (NULL);
}

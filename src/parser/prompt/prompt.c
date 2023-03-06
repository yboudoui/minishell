/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:14:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 17:04:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

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

static bool	syntaxer(t_list *root)
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

t_prompt	prompt_create(char *input)
{
	t_token_list	lexer_output;

	if (input == NULL)
		return (NULL);
	lexer_output = lexer(input);
	if (lexer_output == NULL)
		return (NULL);
	syntaxer((t_list *)&lexer_output);
	return ((t_prompt)lexer_output);
}

void	prompt_destroy(void *data)
{
	if (data == NULL)
		return ;
	list_clear(&data, commande_destroy);
	free(data);
}

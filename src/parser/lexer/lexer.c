/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:58:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 18:02:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	*token_clean(void *input)
{
	t_token_list	*lst;

	lst = input;
	if ((*lst)->token->type == TOKEN_SPACES)
		return (NULL);
	return (token_dup((*lst)->token));
}

static void	*token_merge(void *input)
{
	t_token			out;
	t_token_list	*lst;

	lst = input;
	if ((*lst)->token->type & TOKEN_IO)
	{
		if ((*lst)->next == NULL)
			return (NULL);
		if ((*lst)->next->token->type & TOKEN_IO)
			return (NULL);
		out = token_dup((*lst)->next->token);
		out->type = (*lst)->token->type;
		(*lst) = (*lst)->next;
		return (out);
	}
	else if ((*lst)->token->type & (TOKEN_WORD | TOKEN_PIPE))
		return (token_dup((*lst)->token));
	return (NULL);
}

t_token_list	lexer(char *input)
{
	t_token_list	output;
	t_token_list	new;
	t_token_list	clean;

	output = NULL;
	if (input == NULL)
		return (NULL);
	if (tokenizer(input, (t_list *)&output))
		return (NULL);
	clean = list_subset(output, token_clean);
	new = list_subset(clean, token_merge);
	return (list_clear(&output, token_destroy), new);
}

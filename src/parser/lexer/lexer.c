/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:58:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 07:45:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	*token_merge(void *input)
{
	t_token			out;
	t_token_list	*lst;

	lst = input;
	if (lst == NULL || (*lst) == NULL)
		return (NULL);
	if ((*lst)->token->type & TOKEN_IO)
	{
		out = token_dup((*lst)->token);
		(*lst) = (*lst)->next;
		if ((*lst) == NULL || (*lst)->token->type & TOKEN_OPERATOR)
			return (token_destroy(out), NULL);
		while ((*lst)->token->type == TOKEN_SPACES)
			(*lst) = (*lst)->next;
		if ((*lst) == NULL || (*lst)->token->type & TOKEN_OPERATOR)
			return (token_destroy(out), NULL);
		free(out->input);
//		out->type |= (*lst)->token->type;
		out->input = ft_strdup((*lst)->token->input);
		(*lst) = (*lst)->next;
		return (out);
	}
	return (token_dup((*lst)->token));
}

static void	remove_quotes(void *input, void *_)
{
	t_token	token;
	char	*trimed;

	(void)_;
	token = input;
	if (token == NULL)
		return ;
	if (token->type & (TOKEN_DOUBLE_QUOTES | TOKEN_SIMPLE_QUOTES))
	{
		trimed = ft_strtrim(token->input,
				(char *[]){"'", "\""}[token->type == TOKEN_DOUBLE_QUOTES]);
		free(token->input);
		token->input = trimed;
	}
}

t_token_list	lexer(char *input)
{
	t_token_list	output;
	t_token_list	merged;

	output = NULL;
	if (input == NULL)
		return (NULL);
	if (tokenizer(input, (t_list *)&output))
		return (NULL);
	list_iter(output, remove_quotes, NULL);
	merged = list_subset(output, token_merge);
	list_clear(&output, token_destroy);
	return (merged);
}

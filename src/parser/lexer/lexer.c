/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:58:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/20 17:57:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "minishell.h"

static void	*token_merge_operator(void *input)
{
	t_token			out;
	t_token_list	*lst;

	lst = input;
	if (lst == NULL || (*lst) == NULL)
		return (NULL);
	if ((*lst)->token->type & TOKEN_IO)
	{
		out = token_create((*lst)->token->type, ft_strdup(""));
		(*lst) = (*lst)->next;
		while ((*lst) && ((*lst)->token->type == TOKEN_SPACES))
			(*lst) = (*lst)->next;
		while ((*lst) && ((*lst)->token->type & TOKEN_MERGE))
		{
			out->type |= (*lst)->token->type;
			str_merge_to(&out->input, ft_strdup((*lst)->token->input));
			(*lst) = (*lst)->next;
		}
		return (out);
	}
	return (token_dup((*lst)->token));
}

static void	*token_merge(void *input)
{
	t_token			out;
	t_token_list	*lst;

	lst = input;
	if (lst == NULL || (*lst) == NULL)
		return (NULL);
	if ((*lst)->token->type & TOKEN_SPACES)
		return (NULL);
	if ((*lst)->token->type & TOKEN_OPERATOR)
		return (token_dup((*lst)->token));
	if ((*lst)->token->type & TOKEN_MERGE)
	{
		out = token_dup((*lst)->token);
		if ((*lst)->next && (*lst)->next->token->type & TOKEN_OPERATOR)
			return (out);
		(*lst) = (*lst)->next;
		while ((*lst) && ((*lst)->token->type & TOKEN_MERGE))
		{
			out->type |= (*lst)->token->type;
			str_merge_to(&out->input, ft_strdup((*lst)->token->input));
			(*lst) = (*lst)->next;
		}
		return (out);
	}
	return (token_dup((*lst)->token));
}

void	expand_variable(void *token, void *_)
{
	t_token	input;

	(void)_;
	input = token;
	if (input == NULL)
		return ;
	if (input->type & TOKEN_HERE_DOCUMENT)
		return ;
	token_expand_variable(input);
}

t_token_list	lexer(char *input)
{
	t_token_list	output;
	t_token_list	merged;
	t_token_list	operator;

	output = checker(input);
	if (output == NULL)
		return (NULL);
	operator = list_subset(output, token_merge_operator);
	list_iter(operator, expand_variable, NULL);
	list_clear(&output, token_destroy);
	merged = list_subset(operator, token_merge);
	list_clear(&operator, token_destroy);
	return (merged);
}

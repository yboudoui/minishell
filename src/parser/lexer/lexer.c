/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:58:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/19 15:30:15 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "minishell.h"

static void	*token_merge(void *input)
{
	t_token			out;
	t_token_list	*lst;

	lst = input;
	if (lst == NULL || (*lst) == NULL)
		return (NULL);
	if ((*lst)->token->type == TOKEN_SPACES)
		return (NULL);
	if ((*lst)->token->type == TOKEN_PIPE)
		return (token_dup((*lst)->token));
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

/* static char	*check_syntax(t_token_list lst) */
/* { */
/* 	t_token_type	last; */

/* 	if (lst == NULL) */
/* 		return ("Impossible happend\n"); */
/* 	last = TOKEN_WORD; */
/* 	while (lst) */
/* 	{ */
/* 		if (lst->token->type & TOKEN_OPERATOR && last & TOKEN_OPERATOR) */
/* 			return (g_global.exit_code = 2, "Syntax error\n"); */
/* 		last = lst->token->type; */
/* 		lst = lst->next; */
/* 	} */
/* 	return (NULL); */
/* } */

static char	*check_syntax(t_token_list tokens)
{
	  t_token_list current = tokens;
	  // Check if the first token is an operator or special character
	if (current && current->token->type & (TOKEN_OPERATOR | TOKEN_SPACES)) 
		return (g_global.exit_code = 2, "syntax error near unexpected token\n");

	while (current) {
		t_token_type token_type = current->token->type;
		
		// Case: Consecutive redirections (>, >>, <, <<) with or without spaces
		if (token_type & (TOKEN_REDIRECT_OUT | TOKEN_REDIRECT_OUT_APPEND |
					TOKEN_REDIRECT_IN | TOKEN_HERE_DOCUMENT)) {
			t_token_list next_nonspace = current->next;
			while (next_nonspace && (next_nonspace->token->type & TOKEN_SPACES)) {
				next_nonspace = next_nonspace->next;
			}
			if (next_nonspace && (next_nonspace->token->type & (TOKEN_REDIRECT_OUT | TOKEN_REDIRECT_OUT_APPEND |
							TOKEN_REDIRECT_IN | TOKEN_HERE_DOCUMENT))) 
				return (g_global.exit_code = 2, "syntax error near unexpected redirection\n");
		}

		// Case: Special characters that should be followed by a word
		if (token_type & (TOKEN_PIPE | TOKEN_REDIRECT_OUT | TOKEN_REDIRECT_OUT_APPEND |
					TOKEN_REDIRECT_IN | TOKEN_HERE_DOCUMENT)) {
			t_token_list next_nonspace = current->next;
			while (next_nonspace && (next_nonspace->token->type & TOKEN_SPACES)) {
				next_nonspace = next_nonspace->next;
			}
			if (!next_nonspace) {
				return (g_global.exit_code = 2, "syntax error near unexpected token\n");
			}
		}
		current = current->next;
	}
	return (NULL);
}

void	expand_variable(void *token, void *_)
{
	t_token	input;

	(void)_;
	input = token;
	if (input == NULL)
		return ;
	token_expand_variable(input);
}

void	print(void *token, void *_)
{
	t_token	input;

	(void)_;
	input = token;
	if (input == NULL)
		return ;
	printf("[%s]", input->input);
}

t_token_list	lexer(char *input)
{
	char			*error;
	t_token_list	output;
	t_token_list	merged;

	output = NULL;
	if (input == NULL)
		return (NULL);
	error = tokenizer(input, (t_list *)&output);
	if (error)
		return (ft_putstr_fd(error, 2), NULL);
	list_iter(output, remove_quotes, NULL);
	list_iter(output, expand_variable, NULL);
	error = check_syntax(output);
	if (error)
	{
		list_clear(&output, token_destroy);
		return (ft_putstr_fd(error, 2), NULL);
	}
	merged = list_subset(output, token_merge);
	list_clear(&output, token_destroy);
	return (merged);
}

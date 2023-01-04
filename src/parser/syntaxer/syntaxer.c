/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:19:08 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 14:26:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct e_expression {
	t_expression_type	type;
	char				**input;
}	t_expression;

typedef enum e_error {
	ERROR,
	ERROR_LEXER_EOF,
	NO_CHANGE,
	SUCCES,
}	t_error;

typedef struct s_grammar_dependency {
//	t_token_type			prerequisite;
	t_token_type			conditional;
	t_token_type			required;
}	t_grammar_dependency;

const t_grammar_dependency	*g_grammar_list[MAX_TOKEN] = {
[TOKEN_HERE_DOCUMENT]		=	&{TOKEN_SPACES, TOKEN_WORD},
[TOKEN_REDIRECT_IN]			=	&{TOKEN_SPACES, TOKEN_WORD},
[TOKEN_REDIRECT_OUT_APPEND]	=	&{TOKEN_SPACES, TOKEN_WORD},
[TOKEN_REDIRECT_OUT]		=	&{TOKEN_SPACES, TOKEN_WORD},
};

bool	get_token(t_list *lexer, t_token *output)
{
	if (lexer == NULL || lexer->content == NULL)
		return (false);
	(*output) = (*lexer)->content;
	(*lexer) = (*lexer)->next;
	return (true);
}

t_error	grammar_evaluate(t_list lexer, t_grammar_dependency dependency)
{
	t_token	token;

	if (!get_token(&lexer, &token))
		return (ERROR_LEXER_EOF);
	if (token->type != dependency.prerequisite)
		return (NO_CHANGE);

	if (!get_token(&lexer, &token))
		return (ERROR_LEXER_EOF);
	if (token->type == dependency.conditional)
		if (!get_token(&lexer, &token))
			return (ERROR_LEXER_EOF);

	if (token->type != dependency.required)
		return (ERROR);
	//do something here
	return (SUCCES);
}


t_error	grammar_command(t_list lexer, t_expression *expression)
{
	t_token	token;

	if (lexer == NULL)
		return (ERROR_LEXER_EOF);
	token = lexer->content;
	if (token->type != TOKEN_WORD)
		return (NO_CHANGE);
}

t_list	parser(t_list lexer)
{
	t_token					token;
	t_grammar_dependency	dependency;

	while (lexer)
	{
		token = lexer->content;
		dependency = g_grammar_list[token->type];
		if (!dependency)
			//??
		if (grammar_evaluate(lexer, g_redirect_in) == ERROR);
			return (NULL);
		lexer = lexer->next;
	}
	return (NULL);
}

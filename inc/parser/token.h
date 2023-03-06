/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:13:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 18:48:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "memory.h"
# include "string.h"
# include "list.h"

typedef enum e_token_type {
	TOKEN_SPACES				=	(1U << 0),
	TOKEN_WORD					=	(1U << 1),
	TOKEN_DOUBLE_QUOTES			=	(1U << 2),
	TOKEN_SIMPLE_QUOTES			=	(1U << 3),
//	TOKEN_WILDCARD				=	(1U << 4),
//	TOKEN_COMMANDE				=	(1U << 5),
	TOKEN_REDIRECT_IN			=	(1U << 6),
	TOKEN_HERE_DOCUMENT			=	(1U << 7),
	TOKEN_PIPE					=	(1U << 8),
	TOKEN_REDIRECT_OUT			=	(1U << 9),
	TOKEN_REDIRECT_OUT_APPEND	=	(1U << 10),
//	TOKEN_AND					=	(1U << 11),
//	TOKEN_OR					=	(1U << 12),
//	TOKEN_SUBSHELL				=	(1U << 13),
	MAX_TOKEN					=	(1U << 14),
	TOKEN_IO					=	(0
	| TOKEN_REDIRECT_IN
	| TOKEN_HERE_DOCUMENT
	| TOKEN_REDIRECT_OUT
	| TOKEN_REDIRECT_OUT_APPEND),
	TOKEN_OPERATOR				=	(0
	| TOKEN_IO
	| TOKEN_PIPE)
}	t_token_type;

typedef struct s_token		*t_token;

struct s_token {
	void			*input;
	t_token_type	type;
};

t_token			token_create(t_token_type type, void *substr);
t_token			token_dup(t_token src);
void			token_destroy(void *input);
bool			token_syntaxer(t_list *root);
char			*tokenizer(char *input, t_list *out);

typedef struct s_token_list	*t_token_list;

struct s_token_list {
	t_token			token;
	t_token_list	next;
	t_token_list	prev;
};

t_token_list	lexer(char *input);

#endif

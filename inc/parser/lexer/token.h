/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:13:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/28 13:28:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "memory.h"
# include "string.h"
# include "list.h"

typedef enum e_token_type {
	TOKEN_SPACES				=	(1 << 0),
	TOKEN_WORD					=	(1 << 1),
	TOKEN_DOUBLE_QUOTES			=	(1 << 2),
	TOKEN_SIMPLE_QUOTES			=	(1 << 3),
	TOKEN_WILDCARD				=	(1 << 4),
	TOKEN_COMMANDE				=	(1 << 5),
	TOKEN_REDIRECT_IN			=	(1 << 6),
	TOKEN_HERE_DOCUMENT			=	(1 << 7),
	TOKEN_PIPE					=	(1 << 8),
	TOKEN_REDIRECT_OUT			=	(1 << 9),
	TOKEN_REDIRECT_OUT_APPEND	=	(1 << 10),
	TOKEN_AND					=	(1 << 11),
	TOKEN_OR					=	(1 << 12),
	TOKEN_SUBSHELL				=	(1 << 13),
	MAX_TOKEN					=	(1 << 14),
}	t_token_type;

typedef struct s_token	*t_token;

struct s_token {
	char			*input;
	t_token_type	type;
};

t_token	token_create(t_token_type type, char *substr);
t_token	token_dup(t_token src);
void	token_destroy(void *input);
bool	token_syntaxer(t_list *root);
char	*tokenizer(char *input, t_list *out);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:52:03 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 10:24:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "memory.h"
# include "string.h"
# include "list.h"

typedef enum e_token_type {
	TOKEN_REDIRECT_IN,
	TOKEN_SPACES,
	TOKEN_HERE_DOCUMENT,
	TOKEN_WILDCARD,
	TOKEN_SEMICOLON,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_SIMPLE_QUOTES,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_OUT_APPEND,
	TOKEN_REDIRECT_ERR,
	TOKEN_REDIRECT_ERR_APPEND,
	TOKEN_BACKGROUND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SUBSHELL,
	MAX_TOKEN
}	t_token_type;

typedef struct s_token	*t_token;

struct s_token {
	t_token_type	type;
	char			*input;
};

t_token	token_create(t_token_type type, char *substr);
void	token_destroy(void *input);
t_token	token_match(char *str, t_token_type type, char *start, char *end);
bool	token_founded(char *str, t_token *output);

#endif

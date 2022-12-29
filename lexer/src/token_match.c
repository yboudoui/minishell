/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:35:01 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/29 18:47:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

typedef struct s_token_patern {
	t_token_type	type;
	char			**field;
	t_fp_is_charset	charset;
	char		*match;
}		t_token_patern;

static const t_token_patern	g_token_patern_list[MAX_TOKEN] = {
{TOKEN_SPACES,				.charset = is_space},

{TOKEN_SUBSHELL,			.field = (char *[]){"(", ")"}},
{TOKEN_DOUBLE_QUOTES,		.field = (char *[]){"\"", "\""}},
{TOKEN_SIMPLE_QUOTES,		.field = (char *[]){"'", "'"}},

{TOKEN_WILDCARD,			.match = "*"},
{TOKEN_SEMICOLON,			.match = ";"},
{TOKEN_HERE_DOCUMENT,		.match = "<<"},
{TOKEN_REDIRECT_IN,			.match = "<"},
{TOKEN_REDIRECT_OUT_APPEND,	.match = ">>"},
{TOKEN_REDIRECT_OUT,		.match = ">"},
{TOKEN_REDIRECT_ERR_APPEND,	.match = "2>>"},
{TOKEN_REDIRECT_ERR,		.match = "2>"},
{TOKEN_AND,					.match = "&&"},
{TOKEN_BACKGROUND,			.match = "&"},
{TOKEN_OR,					.match = "||"},
{TOKEN_PIPE,				.match = "|"},
{.type = MAX_TOKEN}
};

#include <stdio.h>
static bool	token_search(char *str, t_token_patern patern, t_token *output)
{
	char	*tmp;

	tmp = NULL;
	(*output) = NULL;
	if (patern.charset)
		tmp = str_slice_charset(str, patern.charset);
	else if (patern.match)
		tmp = str_slice_prefix(str, patern.match);
	else if (patern.field)
	{
		if (ft_strncmp(str, patern.field[0], ft_strlen(patern.field[0])) != 0)
			return (false);
		tmp = str_slice_section(str, patern.field[0], patern.field[1]);
	}
	if (!tmp)
		return (patern.field != NULL);
	(*output) = token_create(patern.type, tmp);
	return (false);
}

bool	token_founded(char *str, t_token *output)
{
	size_t	index;

	(*output) = NULL;
	index = 0;
	while (g_token_patern_list[index].type != MAX_TOKEN)
	{
		if (*output)
			return (false);
		if (token_search(str, g_token_patern_list[index], output))
			return (true);
		index++;
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:35:01 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 18:10:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "show.h"

typedef struct s_token_patern {
	t_token_type	type;
	char			**field;
	t_fp_is_charset	charset;
	char			*match;
	char			*error;
}		t_token_patern;

static const t_token_patern	g_token_patern_list[MAX_TOKEN] = {
{TOKEN_SUBSHELL,
	.field = (char *[]){"(", ")"},
	.error = "Incomplet field, missing parenthesis",
},
{TOKEN_DOUBLE_QUOTES,
	.field = (char *[]){"\"", "\""},
	.error = "Incomplet field, missing double quote",
},
{TOKEN_SIMPLE_QUOTES,
	.field = (char *[]){"'", "'"},
	.error = "Incomplet field, missing single quote",
},
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
{TOKEN_SPACES,				.charset = is_space},
{.type = MAX_TOKEN}
};

static bool	token_slice(char *str, t_token_patern patern, t_token *output)
{
	char	*tmp;

	tmp = NULL;
	(*output) = NULL;
	if (patern.charset)
		tmp = str_slice_charset(str, patern.charset);
	else if (patern.match)
		tmp = str_slice_prefix(str, patern.match);
	else if (patern.field)
		if (str_must_slice_section(str, patern.field, &tmp) == -1)
			return (print_error(patern.error), true);
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
		if (token_slice(str, g_token_patern_list[index], output))
			return (true);
		index++;
	}
	return (false);
}

bool	token_match(char *str, t_list *output)
{
	t_token	token;
	size_t	index;

	(*output) = NULL;
	index = 0;
	while (str[index])
	{
		token = NULL;
		if (token_founded(&str[index], &token))
			return (list_clear(output, token_destroy), false);
		if (token)
		{
			if (index)
				list_create_back(output,
					token_create(TOKEN_WORD, ft_substr(str, 0, index)));
			list_create_back(output, token);
			str += index + ft_strlen(token->input);
			index = 0;
		}
		else
			index += 1;
	}
	if (index)
		list_create_back(output,
			token_create(TOKEN_WORD, ft_substr(str, 0, index)));
	return (true);
}

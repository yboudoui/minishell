/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:35:01 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/19 17:49:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

typedef struct s_token_patern {
	t_token_type	type;
	char			**field;
	t_fp_charset	charset;
	char			*match;
	char			*error;
}		t_token_patern;

static const t_token_patern	g_token_patern_list[MAX_TOKEN] = {
{TOKEN_DOUBLE_QUOTES,
	.field = (char *[]){"\"", "\""},
	.error = "Incomplet field, missing double quote\n",
},
{TOKEN_SIMPLE_QUOTES,
	.field = (char *[]){"'", "'"},
	.error = "Incomplet field, missing single quote\n",
},
{TOKEN_HERE_DOCUMENT,		.match = "<<"},
{TOKEN_REDIRECT_IN,			.match = "<"},
{TOKEN_REDIRECT_OUT_APPEND,	.match = ">>"},
{TOKEN_REDIRECT_OUT,		.match = ">"},
{TOKEN_PIPE,				.match = "|"},
{TOKEN_SPACES,				.charset = is_space},
{.type = MAX_TOKEN}
};

static char	*token_slice(char *str, t_token_patern patern, t_token *output)
{
	char	*tmp;

	tmp = NULL;
	if (patern.charset)
		tmp = str_slice_charset(str, patern.charset);
	else if (patern.match)
		tmp = str_slice_prefix(str, patern.match);
	else if (patern.field)
		if (str_must_slice_section(str, patern.field, &tmp) == -1)
			return (patern.error);
	(*output) = token_create(patern.type, tmp);
	return (NULL);
}

static char	*token_founded(char *str, t_token *output)
{
	size_t	index;
	char	*error;

	(*output) = NULL;
	index = 0;
	while (g_token_patern_list[index].type != MAX_TOKEN)
	{
		if (*output)
			return (NULL);
		error = token_slice(str, g_token_patern_list[index], output);
		if (error)
			return (error);
		index++;
	}
	return (NULL);
}

static bool	token_list_create_back_word(t_list *root, char *input, size_t size)
{
	char	*word;
	t_token	token;

	if (size == 0)
		return (false);
	word = ft_substr(input, 0, size);
	if (word)
	{
		token = token_create(TOKEN_WORD, word);
		if (token)
			return (list_create_back(root, token), true);
	}
	return (free(word), false);
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

char	*tokenizer(char *input, t_list *out)
{
	char	*error;
	t_token	token;
	size_t	index;

	index = 0;
	while (input[index])
	{
		token = NULL;
		error = token_founded(&input[index], &token);
		if (error)
			return (list_clear(out, token_destroy), error);
		if (token)
		{
			token_list_create_back_word(out, input, index);
			list_create_back(out, token);
			input += index + ft_strlen(token->input);
			index = 0;
		}
		else
			index += 1;
	}
	token_list_create_back_word(out, input, index);
	return (list_iter(*out, remove_quotes, NULL), NULL);
}

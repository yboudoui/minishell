/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:49:10 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 10:28:21 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "modules.h"

typedef t_token					(*t_fp_token_handler)(char *str);
static const t_fp_token_handler	g_token_handlers_list[MAX_TOKEN] = {
	token_is_redirect_in,
	token_is_here_document,
	token_is_wildcard,
	token_is_spaces,
	token_is_semicolon,
	token_is_subshell,
	token_is_double_quote,
	token_is_simple_quote,
	token_is_redirect_out_append,
	token_is_redirect_out,
	token_is_redirect_err_append,
	token_is_redirect_err,
	token_is_and,
	token_is_background,
	token_is_or,
	token_is_pipe,
	NULL
};

bool	token_founded(char *str, t_token *output)
{
	size_t	index;

	index = 0;
	while (g_token_handlers_list[index])
	{
		(*output) = g_token_handlers_list[index++](str);
		if (*output)
			return (true);
	}
	return (false);
}

t_token	token_create(t_token_type type, char *substr)
{
	t_token	output;

	if (substr == NULL)
		return (NULL);
	output = ft_calloc(1, sizeof(struct s_token));
	if (output)
		(*output) = (struct s_token){type, substr};
	return (output);
}

void	token_destroy(void *input)
{
	t_token	token;

	token = input;
	if (token == NULL)
		return ;
	free(token->input);
	free(token);
}

t_token	token_match(char *str, t_token_type type, char *start, char *end)
{
	size_t	len;
	char	*tmp;

	if (!str || !start)
		return (NULL);
	len = ft_strlen(start);
	if (ft_strncmp(str, start, len) != 0)
		return (NULL);
	if (end)
	{
		tmp = str + len;
		tmp = ft_strnstr(tmp, end, ft_strlen(tmp));
		if (!tmp)
			return (NULL);
		len = (tmp + ft_strlen(end)) - str;
	}
	return (token_create(type, ft_substr(str, 0, len)));
}

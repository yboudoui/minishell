/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:13:48 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/25 18:46:18 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "modules.h"

const static t_fp_token_handler	g_token_handlers_list[MAX_TOKEN] = {
	is_redirect_in,
	is_semicolon,
	is_subshell,
	is_double_quote,
	is_simple_quote,
	is_redirect_out_append,
	is_redirect_out,
	is_redirect_err_append,
	is_redirect_err,
	is_and,
	is_background,
	is_or,
	is_pipe,
	NULL
};

static bool	token_founded(char *str, t_token *output)
{
	size_t	index;

	index = 0;
	while (g_token_handlers_list[index])
	{
		(*output) = g_token_handlers_list[index++](&str);
		if (*output)
			return (true);
	}
	return (false);
}

void	lexer(char *str, t_list *output)
{
	t_token	tmp;
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (token_founded(&str[index], &tmp) == false)
		{
			index += 1;
			continue ;
		}
		if (index)
			list_create_back(output,
				token_create(TOKEN_WORD, ft_substr(str, 0, index)));
		if (tmp)
		{
			list_create_back(output, tmp);
			index += ft_strlen(tmp->input);
		}
		str += index;
		index = 0;
	}
	if (index)
		list_create_back(output,
			token_create(TOKEN_WORD, ft_substr(str, 0, index)));
}

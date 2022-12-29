/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:13:48 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/29 18:50:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "show.h"

#include <stdio.h>

void	lexer(char *str, t_list *output)
{
	t_token	word;
	t_token	token;
	bool	error;
	size_t	index;

	index = 0;
	while (str[index])
	{
		error = token_founded(&str[index], &token);
		if (error)
		{
			print_error("parsing during lexing");
			return ;
		}
		if (token)
		{
			word = token_create(TOKEN_WORD, ft_substr(str, 0, index));
			list_create_back(output, word);
			list_create_back(output, token);
			str += ft_strlen(word->input) + ft_strlen(token->input);
			index = 0;
		}
		else
			index += 1;
	}
	if (index)
	{
		word = token_create(TOKEN_WORD, ft_substr(str, 0, index));
		list_create_back(output, word);
	}
}

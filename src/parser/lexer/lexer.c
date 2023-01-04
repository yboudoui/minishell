/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:13:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 18:43:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "show.h"

void	print_lexer_output(t_list lexer_output)
{
	if (!lexer_output)
		return ((void)print_error("no token list"));
	printf("~$ ");
	ft_lstiter(lexer_output, print_colored_token);
	printf("\n");
}

bool	lexer_handler(char *input)
{
	t_list	lexer_output;

	lexer_output = NULL;
	if (!token_match(input, &lexer_output))
		return (false);
	print_lexer_output(lexer_output);

	token_list_sanitizer(lexer_output);
	print_lexer_output(lexer_output);

	list_clear(&lexer_output, token_destroy);

	return (true);
}

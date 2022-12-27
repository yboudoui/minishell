/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:04:46 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 10:46:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdio.h>
#include "lexer.h"

void	print_error(char *str)
{
	printf("\033[0;31mERROR: %s\n\033[0m", str);
}

void	print_token(void *content)
{
	t_token	input;

	if (content == NULL)
		return ;
	input = content;
	if (input->type == TOKEN_WORD)
		printf("\e[30m\e[43m%s\e[0m", input->input);
	else if (input->type == TOKEN_DOUBLE_QUOTES)
		printf("\e[30m\e[101m%s\e[0m", input->input);
	else if (input->type == TOKEN_SIMPLE_QUOTES)
		printf("\e[30m\e[105m%s\e[0m", input->input);
	else if (input->type == TOKEN_SPACES)
		printf("\033[47m%s\033[0m", input->input);
	else if (input->type == TOKEN_SUBSHELL)
		printf("\033[104m%s\033[0m", input->input);
	else
		printf("%s", input->input);
}

void	print_lexer_output(t_list lexer_output)
{
	if (!lexer_output)
	{
		print_error("no token list");
		return ;
	}
	printf("~$ ");
	ft_lstiter(lexer_output, print_token);
	printf("\n");
}

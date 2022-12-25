/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/25 18:47:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdio.h>
#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>

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
	else
		printf("%s", input->input);
}

void	print_lexer_output(t_list lexer_output)
{
	printf("~$ ");
	ft_lstiter(lexer_output, print_token);
	printf("\n");
}

void	print_error(char *str)
{
	printf("\033[0;31mERROR: %s\n\033[0m", str);
}

void	parsing(char *input)
{
	t_list	lexer_output;

	lexer_output = NULL;
	lexer(input, &lexer_output);
	if (!lexer_output)
		print_error("no token list");
	else
	{
		print_lexer_output(lexer_output);
		list_clear(&lexer_output, token_destroy);
	}
}

int	main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		rl_on_new_line();
		line = readline("~$ ");
		if (NULL == line)
			break ;
		parsing(line);
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}

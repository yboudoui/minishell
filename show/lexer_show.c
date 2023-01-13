/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:04:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 08:31:35 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "show.h"

void	print_error(char *str)
{
	printf("\033[0;31mERROR: %s\n\033[0m", str);
}

void	print_colored_token(void *content)
{
	t_token	input;

	if (content == NULL)
		return ((void)printf("_\n"));
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
		printf("\e[42m%s\e[0m", input->input);
	printf(" ");
}

void	warn_on_empty_list(t_list lst)
{
	if (!lst)
		return ((void)print_error("no token list"));
}

void	print_colored_token_list(char *name, t_list lst)
{
	if (!lst)
		return ;
	if (name)
		printf("%s", name);
	ft_lstiter(lst, print_colored_token);
	printf("\n");
}

const char	*get_token_type_string(t_token_type type)
{
	const char	*token_type_string[MAX_TOKEN] = {
	[TOKEN_REDIRECT_IN] = "TOKEN_REDIRECT_IN",
	[TOKEN_SPACES] = "TOKEN_SPACES",
	[TOKEN_HERE_DOCUMENT] = "TOKEN_HERE_DOCUMENT",
	[TOKEN_WILDCARD] = "TOKEN_WILDCARD",
	[TOKEN_DOUBLE_QUOTES] = "TOKEN_DOUBLE_QUOTES",
	[TOKEN_SIMPLE_QUOTES] = "TOKEN_SIMPLE_QUOTES",
	[TOKEN_WORD] = "TOKEN_WORD",
	[TOKEN_PIPE] = "TOKEN_PIPE",
	[TOKEN_REDIRECT_OUT] = "TOKEN_REDIRECT_OUT",
	[TOKEN_REDIRECT_OUT_APPEND] = "TOKEN_REDIRECT_OUT_APPEND",
	[TOKEN_AND] = "TOKEN_AND",
	[TOKEN_OR] = "TOKEN_OR",
	[TOKEN_SUBSHELL] = "TOKEN_SUBSHELL",
	[TOKEN_COMMANDE] = "TOKEN_COMMANDE",
	};

	if (type >= 0 && type < MAX_TOKEN)
		return (token_type_string[type]);
	return (NULL);
}

void	print_token_type(void *content)
{
	t_token	token;

	token = content;
	printf("%s\n", get_token_type_string(token->type));
}

void	print_lexer_token_type(t_list lexer_output)
{
	if (!lexer_output)
		return ((void)print_error("no token list"));
	ft_lstiter(lexer_output, print_token_type);
}

void	print_argv(void *content)
{
	char	**input;

	if (!content)
		return ;
	input = content;
	while(*input)
	{
		printf("\033[30m\033[104m[%s]\033[0m", *input);
		input++;
	}
	printf("\n");
}



void	print_commande_line(void *content)
{
	t_commande		cmd;
	t_token_type	*type;

	if (!content)
		return ;
	type = content;
	if (*type == TOKEN_PIPE)
		return ((void)printf(" PIPE \n"));
	cmd = content;
	printf("--------------------------\n");
	print_colored_token_list("\targv: ", cmd->argv);
	print_colored_token_list("\tredir_in: ", cmd->redir_in);
	print_colored_token_list("\tredir_out: ", cmd->redir_out);
	print_colored_token_list("\tredir_out_append: ", cmd->redir_out_append);
	print_colored_token_list("\there_document: ", cmd->here_document);
	printf("--------------------------\n");
}

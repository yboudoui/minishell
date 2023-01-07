/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:13:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/07 16:42:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "show.h"

void	token_destroy_by_type(void *input)
{
	t_token_type	*type;

	if (!input)
		return ;
	type = input;
	if ((*type) == TOKEN_COMMANDE)
		commande_destroy(input);
	else
		token_destroy(input);
}

bool	lexer_handler(char *input)
{
	t_list	lexer_output;

	lexer_output = NULL;
	if (!token_match(input, &lexer_output))
		return (false);
	print_colored_token_list("~$ ", lexer_output);
	token_list_sanitizer(&lexer_output);
	print_colored_token_list("~$ ", lexer_output);
	token_syntaxer(&lexer_output);
	ft_lstiter(lexer_output, print_commande_line);
	return (list_clear(&lexer_output, token_destroy_by_type), true);
}

/*
mega lol test
infile < "qweqw" | grep -la | ls -la << here_doc| test | $arg 'asdad"asdadasd"asdasd' > test.c | grep < sdkjfh >> kusdhfj  > sdfjh "uyghd " 'khgd f' << lol << 1 << 2 << 3  >> ds >>fdd >>a  >da > d >ds >d < 1 < 2 < 3
*/

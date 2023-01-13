/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:14:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 08:20:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

#include "show.h"

void	prompt_destroy(void *data)
{
	t_prompt	input;

	input = data;
	if (input == NULL)
		return ;
	list_clear(&input->heredoc, token_destroy);
	list_clear(&input->commande, commande_destroy);
	free(input);
}

t_prompt	prompt_create(char *input)
{
	char		*error;
	t_list		lexer_output;
	t_prompt	out;

	if (input == NULL)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_prompt));
	if (out == NULL)
		return (NULL);
	lexer_output = NULL;
	error = lexer(input, &lexer_output);
	if (error)
		return (print_error(error), NULL);
	syntaxer(&lexer_output);
	out->commande = lexer_output;
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:14:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 15:19:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	prompt_destroy(void *data)
{
	if (data == NULL)
		return ;
	list_clear(&data, commande_destroy);
	free(data);
}

t_prompt	prompt_create(char *input)
{
	char		*error;
	t_list		lexer_output;

	if (input == NULL)
		return (NULL);
	lexer_output = NULL;
	error = lexer(input, &lexer_output);
	if (error)
		return (NULL); //ERROR
	syntaxer(&lexer_output);
	return ((t_prompt)lexer_output);
}

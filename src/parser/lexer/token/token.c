/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:49:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 17:54:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "modules.h"

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
//	token->input = NULL;
	free(token);
//	token = NULL;
}

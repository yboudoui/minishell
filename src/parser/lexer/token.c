/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:49:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/19 11:40:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "environment.h"

t_token	token_create(t_token_type type, void *substr)
{
	t_token	output;

	if (substr == NULL)
		return (NULL);
	output = ft_calloc(1, sizeof(struct s_token));
	if (output)
		(*output) = (struct s_token){substr, -1, type};
	return (output);
}

void	token_destroy(void *input)
{
	t_token	token;

	token = input;
	if (token == NULL)
		return ;
	free(token->input);
	free(token);
}

t_token	token_dup(t_token src)
{
	if (!src)
		return (NULL);
	return (token_create(src->type, ft_strdup(src->input)));
}

void	token_expand_variable(t_token token)
{
	if (token == NULL)
		return ;
	if (env_find_and_expand_var_to(&token->input))
		token->type |= TOKEN_EXPANDED;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:16:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 19:06:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "show.h"

typedef struct s_grammar_dependency {
	t_token_type			conditional;
	t_token_type			required;
}	t_grammar_dependency;

static t_grammar_dependency	*g_grammar_list[MAX_TOKEN] = {
[TOKEN_HERE_DOCUMENT]		=	&(t_grammar_dependency){TOKEN_SPACES, TOKEN_WORD},
[TOKEN_REDIRECT_IN]			=	&(t_grammar_dependency){TOKEN_SPACES, TOKEN_WORD},
[TOKEN_REDIRECT_OUT_APPEND]	=	&(t_grammar_dependency){TOKEN_SPACES, TOKEN_WORD},
[TOKEN_REDIRECT_OUT]		=	&(t_grammar_dependency){TOKEN_SPACES, TOKEN_WORD},
};

void	sanitizer(t_list *lst, t_grammar_dependency *dependency)
{
	t_token					token;

	if (!lst || !dependency)
		return ;
	token = (*lst)->content;
	if (!token)
		return ;
	printf("%s\n", get_token_type_string(token->type));
	printf("%s\n", get_token_type_string(dependency->conditional));
	if (token->type & dependency->conditional)
	{
		list_remove_one(lst, token_destroy);
	}
/*
	lst = lst->next;
	if (lst == NULL)
		return (false);
	token = lst->content;
	if (token->type != dependency->required)
		return (false);
	return (true);
*/
}

bool	token_list_sanitizer(t_list lst)
{
	t_token					token;
	t_grammar_dependency	*dependency;

	while (lst)
	{
		token = lst->content;
		dependency = g_grammar_list[token->type];
		if (dependency)
			sanitizer(&(lst->next), dependency);
		lst = lst->next;
	}
	return (true);
}

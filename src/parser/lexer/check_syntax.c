/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:48:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/20 18:02:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "minishell.h"

static void	*token_remove_useless_dolar(void *input)
{
	t_token_list	*lst;

	lst = input;
	if (lst == NULL || (*lst) == NULL)
		return (NULL);
	if (string_cmp((*lst)->token->input, "$") == 0
		&& (*lst)->next
		&& (*lst)->next->token->type & TOKEN_QUOTE)
	{
		(*lst)->token->type = TOKEN_SPACES;
		free((*lst)->token->input);
		(*lst)->token->input = ft_strdup("");
	}
	return (token_dup((*lst)->token));
}

static char	*check_syntax(t_token_list lst)
{
	if (lst && lst->token->type & TOKEN_PIPE)
		return ("syntax error near unexpected token\n");
	while (lst)
	{
		if (lst->token->type & TOKEN_IO)
		{
			lst = lst->next;
			while (lst && (lst->token->type & TOKEN_SPACES))
				lst = lst->next;
			if (lst && (lst->token->type & TOKEN_IO))
				return ("syntax error near unexpected redirection\n");
		}
		if (lst->token->type & TOKEN_OPERATOR)
		{
			while (lst && (lst->token->type & TOKEN_SPACES))
				lst = lst->next;
			if (lst == NULL)
				return ("syntax error near unexpected token\n");
		}
		lst = lst->next;
	}
	return (NULL);
}

t_token_list	checker(char *input)
{
	char			*error;
	t_token_list	output;
	t_token_list	removed;

	output = NULL;
	if (input == NULL)
		return (NULL);
	error = tokenizer(input, (t_list *)&output);
	if (error)
		return (ft_putstr_fd(error, 2), NULL);
	error = check_syntax(output);
	if (error)
	{
		g_global.exit_code = 2;
		list_clear(&output, token_destroy);
		return (ft_putstr_fd(error, 2), NULL);
	}
	removed = list_subset(output, token_remove_useless_dolar);
	list_clear(&output, token_destroy);
	return (removed);
}

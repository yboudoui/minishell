/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 18:07:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commande.h"
#include "token.h"

static t_token_type	g_token_type;

static void	*token_by_type(void *input)
{
	t_token_list	*lst;

	lst = input;
	if ((*lst)->token->type & g_token_type)
		return (token_dup((*lst)->token));
	return (NULL);
}

t_commande	commande_create(t_list lst)
{
	t_commande	out;
	const int	redir_in = TOKEN_REDIRECT_IN | TOKEN_HERE_DOCUMENT;
	const int	redir_out = TOKEN_REDIRECT_OUT | TOKEN_REDIRECT_OUT_APPEND;
	const int	remaining = ~(redir_in | redir_out);

	if (!lst)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_commande));
	if (!out)
		return (NULL);
	g_token_type = redir_in;
	out->redir_in = list_subset(lst, token_by_type);
	g_token_type = redir_out;
	out->redir_out = list_subset(lst, token_by_type);
	g_token_type = remaining;
	out->argv = list_subset(lst, token_by_type);
	list_clear(&lst, token_destroy);
	return (out);
}

void	commande_destroy(void *data)
{
	t_commande	cmd;

	cmd = data;
	if (cmd == NULL)
		return ;
	list_clear(&cmd->redir_in, token_destroy);
	list_clear(&cmd->redir_out, token_destroy);
	list_clear(&cmd->argv, token_destroy);
	free(data);
}

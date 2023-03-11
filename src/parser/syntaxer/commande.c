/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/11 12:46:50 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commande.h"

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

	if (!lst)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_commande));
	if (!out)
		return (NULL);
	g_token_type = TOKEN_IO;
	out->redir = list_subset(lst, token_by_type);
	g_token_type = ~TOKEN_IO;
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
	list_clear(&cmd->redir, token_destroy);
	list_clear(&cmd->argv, token_destroy);
	free(data);
}

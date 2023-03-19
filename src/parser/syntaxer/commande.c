/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/19 19:02:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commande.h"

static void	*extract_remaining_token(void *input)
{
	t_token_list	*lst;

	lst = input;
	if ((*lst)->token->type & TOKEN_IO)
		return (NULL);
	if ((*lst)->token->type & TOKEN_MERGE)
		return (token_dup((*lst)->token));
	return (NULL);
}

static void	*extract_io_token(void *input)
{
	t_token_list	*lst;

	lst = input;
	if ((*lst)->token->type & TOKEN_IO)
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
	out->redir = list_subset(lst, extract_io_token);
	out->argv = list_subset(lst, extract_remaining_token);
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

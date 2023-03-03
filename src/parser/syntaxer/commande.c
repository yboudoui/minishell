/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/03 16:02:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commande.h"

t_list	get_input_by_type(t_list *root, t_token_type type)
{
	t_token	token;
	t_token	tmp;
	t_list	new;
	t_list	out;
	t_list	lst;

	new = NULL;
	out = NULL;
	lst = (*root);
	while (lst)
	{
		token = lst->content;
		if (token->type & type)
		{
			if (!lst->next || ((t_token)lst->next->content)->type == type)
			{
				list_clear(root, token_destroy);
				list_clear(&out, token_destroy);
				list_clear(&new, token_destroy);
				return (list_clear(root, token_destroy), NULL);
			}
			tmp = token_dup(lst->next->content);
			tmp->type = token->type;
			list_create_back(&new, tmp);
			lst = lst->next;
		}
		else
			list_create_back(&out, token_dup(token));
		lst = lst->next;
	}
	list_clear(root, token_destroy);
	return ((*root) = out, new);
}

t_commande	commande_create(t_list lst)
{
	t_commande	out;
	const int	redir_in = TOKEN_REDIRECT_IN | TOKEN_HERE_DOCUMENT;
	const int	redir_out = TOKEN_REDIRECT_OUT | TOKEN_REDIRECT_OUT_APPEND;

	if (!lst)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_commande));
	if (out)
		(*out) = (struct s_commande){
			.redir_in = get_input_by_type(&lst, redir_in),
			.redir_out = get_input_by_type(&lst, redir_out),
			.argv = lst
		};
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

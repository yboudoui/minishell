/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/21 11:33:59 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token_list	split_again(t_token_list lst)
{
	char			**splited;
	int				idx;
	t_token			new;
	t_token_list	output;

	output = NULL;
	while (lst)
	{
		if (lst->token->type & (TOKEN_WORD | TOKEN_EXPANDED)
			&& !(lst->token->type & TOKEN_QUOTE))
		{
			splited = ft_split(lst->token->input, is_space);
			idx = -1;
			while (splited[++idx])
			{
				new = token_create(TOKEN_WORD, ft_strdup(splited[idx]));
				list_create_back((t_list *)&output, new);
			}
			string_array_destroy(splited);
		}
		else
			list_create_back((t_list *)&output, token_dup(lst->token));
		lst = lst->next;
	}
	return (output);
}

void	commande_expand_variable(void *commande, void *_)
{
	t_commande	cmd;
	t_list		old;

	(void)_;
	cmd = commande;
	if (cmd == NULL)
		return ;
	old = cmd->argv;
	cmd->argv = (t_list)split_again((t_token_list)cmd->argv);
	list_clear(&old, token_destroy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 19:33:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	token_expand_env_var(void *input, void *_)
{
	t_token	token;

	(void)_;
	token = input;
	if (token == NULL)
		return ;
	if (token->type & (TOKEN_HERE_DOCUMENT | TOKEN_SIMPLE_QUOTES))
		return ;
	env_find_and_expand_var_to(&token->input);
}

static t_token_list	list_join(t_token_list lst)
{
	t_token_list	output;
	t_token			new;

	output = NULL;
	new = NULL;
	while (lst)
	{
		if (new == NULL && (lst->token->type & TOKEN_MERGE))
		{
			new = token_dup(lst->token);
			list_create_back((t_list *)&output, new);
		}
		else if (new && lst->token->type & TOKEN_MERGE)
		{
			str_merge_to(&new->input, ft_strdup(lst->token->input));
			if (lst->token->type & (~TOKEN_WORD))
				new->type = lst->token->type;
		}
		else
		{
			new = NULL;
			list_create_back((t_list *)&output, token_dup(lst->token));
		}
		lst = lst->next;
	}
	return (output);
}

static t_token_list	split_again(t_token_list lst)
{
	char			**splited;
	int				idx;
	t_token			new;
	t_token_list	output;

	output = NULL;
	while (lst)
	{
		if (lst->token->type & (TOKEN_WORD))
		{
			splited = ft_split(lst->token->input, is_space);
			idx = 0;
			while (splited[idx])
			{
				new = token_create(TOKEN_WORD, ft_strdup(splited[idx]));
				list_create_back((t_list *)&output, new);
				idx += 1;
			}
			string_array_destroy(splited);
		}
		else
			list_create_back((t_list *)&output, token_dup(lst->token));
		lst = lst->next;
	}
	return (output);
}

static void	*remove_space(void *input)
{
	t_token_list	*lst;

	lst = input;
	if (lst == NULL || (*lst) == NULL)
		return (NULL);
	if ((*lst)->token->type & TOKEN_SPACES)
		return (NULL);
	return (token_dup((*lst)->token));
}

void	commande_expand_variable(void *commande, void *_)
{
	t_commande	cmd;
	t_list		old;

	(void)_;
	cmd = commande;
	if (cmd == NULL)
		return ;
	list_iter(cmd->argv, token_expand_env_var, NULL);
	old = cmd->argv;
	cmd->argv = (t_list)list_join((t_token_list)cmd->argv);
	list_clear(&old, token_destroy);
	old = cmd->argv;
	cmd->argv = (t_list)split_again((t_token_list)cmd->argv);
	list_clear(&old, token_destroy);
	old = cmd->argv;
	cmd->argv = list_subset(cmd->argv, remove_space);
	list_clear(&old, token_destroy);
	list_iter(cmd->redir, token_expand_env_var, NULL);
}

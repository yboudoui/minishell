/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/15 17:38:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	token_expand_env_var(void *input, void *_)
{
	t_token	token;
	char	*expanded;

	(void)_;
	token = input;
	if (token == NULL)
		return ;
	if (token->type & (TOKEN_HERE_DOCUMENT | TOKEN_SIMPLE_QUOTES))
		return ;
	expanded = env_find_and_expand_var(token->input);
	if (expanded == NULL)
		return ;
	free(token->input);
	token->input = expanded;
	// here deal with var expansion "$var" vs $var
}
/*
t_token_list	list_join(t_token_list lst)
{
	char			*tmp;
	char			**splited;
	t_token_list	output;

	output = NULL;
	while (lst)
	{
		if (lst->next && lst->next->token->type & TOKEN_DOUBLE_QUOTES)
		{
			tmp = lst->token->input;
			lst->token->input = ft_strjoin(tmp, lst->next->token->input);
			free(tmp);
			list_create_back((t_list *)&output, token_dup(lst->token));
			lst = lst->next->next;
			continue ;
		}
		else if (lst->next && lst->next->token->type & TOKEN_WORD)
		{
			tmp = ft_strjoin(lst->token->input, " ");
			free(lst->token->input);
			lst->token->input = ft_strjoin(tmp, lst->next->token->input);
			free(tmp);
			splited = ft_split(lst->token->input, ' ');
				int i = -1;
				while (splited[++i])
				{
					printf("--> %s\n", splited[i]);
					list_create_back((t_list *)&output, token_create(TOKEN_WORD, ft_strdup(splited[i])));
				}
				string_array_destroy(splited);
				lst = lst->next->next;
				continue ;
		}
		else
			list_create_back((t_list *)&output, token_dup(lst->token));
		lst = lst->next;
	}
	return (output);
}
*/

t_token_list	list_join(t_token_list lst)
{
	t_token_list	output;

	output = NULL;
	while (lst)
	{
		if (lst->next && lst->next->token->type & (TOKEN_DOUBLE_QUOTES | TOKEN_SIMPLE_QUOTES))
		{
			list_create_back((t_list *)&output, token_create(lst->next->token->type, ft_strjoin(lst->token->input, lst->next->token->input)));
			lst = lst->next->next;
			continue ;
		}
		else
			list_create_back((t_list *)&output, token_dup(lst->token));
		lst = lst->next;
	}
	return (output);
}

t_token_list	split_again(t_token_list lst)
{
	char			**splited;
	int				idx;
	t_token_list	output;

	output = NULL;
	while (lst)
	{
		if (lst->token->type & (TOKEN_WORD))
		{
			splited = ft_split(lst->token->input, ' ');
			idx = 0;
			while (splited[idx])
			{
				list_create_back((t_list *)&output, token_create(TOKEN_WORD, ft_strdup(splited[idx])));
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

static void	commande_expand_variable(void *commande, void *_)
{
	t_commande	cmd;
	t_list old;

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

int	execution(t_prompt prompt)
{
	if (g_global.prompt == NULL)
		return (EXIT_FAILURE);
	if (!heredoc(prompt))
		return (EXIT_FAILURE);
	list_iter(prompt, commande_expand_variable, NULL);
	g_global.cmds = convertion(prompt);
	pipex(g_global.cmds);
	cmd_list_destroy(&g_global.cmds);
	return (EXIT_SUCCESS);
}

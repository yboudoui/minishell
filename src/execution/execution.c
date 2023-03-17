/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 07:50:07 by yboudoui         ###   ########.fr       */
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

t_token_list	list_join(t_token_list lst)
{
	t_token_list	output;
	char			*joined;
	t_token			new;

	output = NULL;
	while (lst)
	{
		if (lst->next && lst->next->token->type & TOKEN_QUOTE)
		{
			joined = ft_strjoin(lst->token->input, lst->next->token->input);
			new = token_create(lst->next->token->type, joined);
			list_create_back((t_list *)&output, new);
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
			splited = ft_split(lst->token->input, ' '); //by whitspaces!!
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
	t_cmd_list	cmd;

	if (g_global.prompt == NULL)
		return (EXIT_FAILURE);
	if (heredoc(prompt))
		return (EXIT_SUCCESS);
	list_iter(prompt, commande_expand_variable, NULL);
	cmd = convertion(prompt);
	g_global.cmds = cmd;
	pipex(cmd);
	cmd_list_destroy(&g_global.cmds);
	return (EXIT_SUCCESS);
}

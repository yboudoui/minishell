/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/10 18:35:35 by yboudoui         ###   ########.fr       */
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
	expanded = env_find_and_expand_var(token->input);
	if (expanded == NULL)
		return ;
	free(token->input);
	token->input = expanded;
}

static void	commande_expand_variable(void *commande, void *_)
{
	t_commande	cmd;

	(void)_;
	cmd = commande;
	if (cmd == NULL)
		return ;
	list_iter(cmd->argv, token_expand_env_var, NULL);
	list_iter(cmd->redir_in, token_expand_env_var, NULL);
	list_iter(cmd->redir_out, token_expand_env_var, NULL);
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

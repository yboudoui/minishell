/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/01 12:41:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_all_command(t_list env, t_prompt cmd)
{
	while (cmd)
	{
		commande_expand_variable(env, cmd->content);
		cmd = cmd->next;
	}
}

int	execution(t_list env, t_prompt prompt)
{
	if (prompt == NULL)
		return (EXIT_FAILURE);
	if (heredoc(prompt))
		return (EXIT_FAILURE);
	expand_all_command(env, prompt);
	if (pipex(env, prompt))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

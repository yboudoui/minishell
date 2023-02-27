/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 16:27:56 by kdhrif           ###   ########.fr       */
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
	pid_t pid;
	int status;

	if (prompt == NULL)
		return (EXIT_FAILURE);
	if (heredoc(prompt))
		return (EXIT_FAILURE);
	expand_all_command(env, prompt);
	fork_pid(&pid);
	if (pid == 0)
		pipex(env, prompt);
	else
		waitpid(pid, &status, 0);

	return (EXIT_SUCCESS);
}

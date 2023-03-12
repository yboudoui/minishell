/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:26:56 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/12 14:06:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplexer.h"

t_multiplexer	multiplexer_create(char *env[], char *bash, char *minishell)
{
	t_multiplexer	output;

	if (bash == NULL || minishell == NULL)
		return (NULL);
	output = ft_calloc(1, sizeof(struct s_multiplexer));
	if (output == NULL)
		return (NULL);
	output->sh[B_SH] = shell_create(bash);
	output->sh[M_SH] = shell_create(minishell);

	shell_fork(&output->sh[B_SH], env);
	shell_fork(&output->sh[M_SH], env);

	return (output);
}

void	multiplexer_write(t_multiplexer ml, char *cmd)
{
	shell_write(ml->sh[M_SH], cmd);
	shell_write(ml->sh[B_SH], cmd);
}

void	multiplexer_destroy(t_multiplexer ml)
{
	if (ml == NULL)
		return ;

	shell_close_stdin(&ml->sh[B_SH]);
	shell_close_stdin(&ml->sh[M_SH]);
	
	shell_wait_fork(ml->sh[B_SH]);
	shell_wait_fork(ml->sh[M_SH]);

	shell_close_stdout(&ml->sh[B_SH]);
	shell_close_stdout(&ml->sh[M_SH]);
}

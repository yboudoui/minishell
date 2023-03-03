/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:11:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/03 16:03:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
/*
static void	*token_to_string(void *data)
{
	t_token	input;

	input = data;
	if (input == NULL)
		return (NULL);
	return (input->input);
}
*/
t_cmd	cmd_create(t_commande cmd)
{
	t_cmd	output;

	output = ft_calloc(1, sizeof(struct s_cmd));
	output->argv = list_to_array(cmd->argv, token_to_string);
	output->redir_in = cmd->redir_in;
	output->redir_out = cmd->redir_out;
	return (output);
}

void	cmd_destroy(void *data)
{
	t_cmd	input;

	input = data;
	if (input == NULL)
		return ;
	free(input->argv);
	free(input);
}

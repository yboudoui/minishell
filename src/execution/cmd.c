/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:11:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/11 12:51:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	*token_to_string(void *data)
{
	t_token	input;

	input = data;
	if (input == NULL)
		return (NULL);
	return (input->input);
}

t_cmd	cmd_create(t_commande cmd)
{
	t_cmd	output;

	output = ft_calloc(1, sizeof(struct s_cmd));
	output->argv = list_to_array(cmd->argv, token_to_string);
	output->redir = cmd->redir;
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

t_cmd_list	convertion(t_prompt prompt)
{
	t_list	output;

	output = NULL;
	while (prompt)
	{
		list_create_back(&output, cmd_create(prompt->content));
		prompt = prompt->next;
	}
	return ((t_cmd_list)output);
}

void	cmd_list_destroy(void *data)
{
	t_cmd_list	*input;

	input = data;
	if (input == NULL)
		return ;
	list_clear(input, cmd_destroy);
	(*input) = NULL;
}

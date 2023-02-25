/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/25 16:51:22 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"

void pipex(t_list env, t_prompt prompt)
{
	t_list_commande cmd;

	cmd = (t_list_commande)prompt->commande;
	while (cmd)
	{
		infile(cmd->content->redir_in);
		cmd = cmd->next;
	}
	//First checks the redir_in
}

void	*token_to_string(void *data)
{
	t_token	input;

	input = data;
	if (input == NULL)
		return (NULL);
	return (input->input);
}

t_cmd *cmd_create(t_commande cmd)
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->argv = list_to_array(cmd->argv, token_to_string);
	new->redir_in = cmd->redir_in;
	new->redir_out = cmd->redir_out;
	/* new->here_document = cmd->here_document; */
	return (new);
}

int infile(t_list redir_in)
{

	while (redir_in)
	{
		f_open((char *)redir_in->content, O_RDONLY, 0);
		redir_in = redir_in->next;
	}

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/07 16:37:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_list	slice_commande(t_list *lst)
{
	t_token	token;
	t_list	output;

	output = NULL;
	while (*lst)
	{
		token = (*lst)->content;
		if (token->type == TOKEN_PIPE)
			break ;
		else
			list_create_back(&output, token_dup(token));
		(*lst) = (*lst)->next;
	}
	return (output);
}

t_list	get_input_by_type(t_list *root, t_token_type type)
{
	t_token	token;
	t_list	new;
	t_list	out;
	t_list	lst;

	new = NULL;
	out = NULL;
	lst = (*root);
	while (lst)
	{
		token = lst->content;
		if (token->type == type)
		{
			if (!lst->next || ((t_token)lst->next->content)->type == type)
			{
				list_clear(root, token_destroy);
				list_clear(&out, token_destroy);
				list_clear(&new, token_destroy);
				return (NULL);
			}
			list_create_back(&new, token_dup(lst->next->content));
			lst = lst->next;
		}
		else
			list_create_back(&out, token_dup(token));
		lst = lst->next;
	}
	list_clear(root, token_destroy);
	return ((*root) = out, new);
}

void	string_array_destroy(void *data)
{
	char	**input;
	size_t	index;

	if (data == NULL)
		return ;
	index = 0;
	input = data;
	while (input[index])
	{
		free(input[index]);
		index++;
	}
	free(data);
}

char	**list_to_str_array(t_list lst)
{
	size_t	size;
	size_t	index;
	t_token	token;
	char	**out;

	size = list_size(lst);
	if (!size)
		return (NULL);
	out = ft_calloc(size + 1, sizeof(char *));
	if (!out)
		return (NULL);
	index = 0;
	while (index < size)
	{
		token = lst->content;
		out[index] = ft_strdup(token->input);
		if (!out[index])
			return (string_array_destroy(out), NULL);
		lst = lst->next;
		index++;
	}
	return (out);
}

t_commande	commande_create(t_list lst)
{
	t_commande	out;

	if (!lst)
		return (NULL);
	out = ft_calloc(1, sizeof(struct s_commande));
	if (!out)
		return (NULL);
	out->type = TOKEN_COMMANDE;
	out->redir_in = get_input_by_type(&lst, TOKEN_REDIRECT_IN);
	out->redir_out = get_input_by_type(&lst, TOKEN_REDIRECT_OUT);
	out->redir_out_append = get_input_by_type(&lst, TOKEN_REDIRECT_OUT_APPEND);
	out->here_document = get_input_by_type(&lst, TOKEN_HERE_DOCUMENT);
	out->argv = lst;
//	out->argv = list_to_str_array(lst);
//	list_clear(&lst, token_destroy);
	if (out->argv == NULL)
		return (commande_destroy(out), NULL);
	return (out);
}

void	commande_destroy(void *data)
{
	t_commande	cmd;

	if (!data)
		return ;
	cmd = data;
//	string_array_destroy(cmd->argv);
	list_clear(&cmd->redir_in, token_destroy);
	list_clear(&cmd->redir_out, token_destroy);
	list_clear(&cmd->redir_out_append, token_destroy);
	list_clear(&cmd->here_document, token_destroy);
	list_clear(&cmd->argv, token_destroy);
	free(data);
}

bool	token_syntaxer(t_list *root)
{
	t_list	output;
	t_list	lst;
	t_token	token;

	output = NULL;
	lst = (*root);
	while (lst)
	{
		token = lst->content;
		if (token->type == TOKEN_PIPE)
		{
			list_create_back(&output, token_dup(token));
			lst = lst->next;
		}
		else
			list_create_back(&output, commande_create(slice_commande(&lst)));
	}
	list_clear(root, token_destroy);
	(*root) = output;
	return (true);
}

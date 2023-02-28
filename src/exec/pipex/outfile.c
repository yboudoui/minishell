/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:01:53 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/28 14:29:26 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	outfile(t_list redir_out)
{
	int		fd;
	t_token	token;

	if (redir_out == NULL)
	{
		printf("redir_out is null\n");
		return (STDOUT_FILENO);
	}
	fd = -1;
	token = NULL;
	while (redir_out)
	{
		token = redir_out->content;
		if (token->type == TOKEN_REDIRECT_OUT)
			fd = f_open((char *)redir_out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (token->type == TOKEN_REDIRECT_OUT_APPEND)
			fd = f_open((char *)redir_out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1 && redir_out->next == NULL)
			return (-1);
		if (fd != -1 && redir_out->next != NULL)
			close_fd(&fd);
		if (fd != -1 && redir_out->next == NULL)
			return (fd);
		redir_out = redir_out->next;
	}
	return (STDOUT_FILENO);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:21:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/10 19:39:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static inline int	check_infile_status(t_list redir_in, int fd)
{
	if (redir_in == NULL)
		return (-1);
	if (fd == -1 && redir_in->next == NULL)
		return (-1);
	if (fd == -1 && redir_in->next != NULL)
		return (-1);
	return (fd);
}

int	infile(t_list redir_in)
{
	int		fd;
	t_token	token;

	if (redir_in == NULL)
		return (1);
	fd = -1;
	while (redir_in)
	{
		token = redir_in->content;
		if (token->type == TOKEN_REDIRECT_IN)
			fd = f_open((char *)token->input, O_RDONLY, 0);
		else
			fd = *(int *)(token->input);
		if (check_infile_status(redir_in, fd) == -1)
			return (-1);
		if (fd != -1 && redir_in->next != NULL)
			close_fd(&fd);
		if (fd != -1 && redir_in->next == NULL)
			return (fd);
		redir_in = redir_in->next;
	}
	return (1);
}

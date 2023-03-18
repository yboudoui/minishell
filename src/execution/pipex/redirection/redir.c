/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:13:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/18 19:13:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	close_or_assign(int fd_end, int fd_new)
{
	if (fd_new == -1)
	{
		close_fd(&fd_end);
		return (-2);
	}
	if (fd_end != -1)
		close_fd(&fd_end);
	return (fd_new);
}

int	close_all(t_list redir, int fd_infile, int fd_outfile)
{
	t_token	token;

	close_fd(&fd_infile);
	close_fd(&fd_outfile);
	while (redir)
	{
		token = redir->content;
		if (token->type == TOKEN_HERE_DOCUMENT)
			close_fd(&token->fd);
		redir = redir->next;
	}
	return (1);
}

int	manage_redirs(t_list redir, t_pipex *pipex)
{
	t_token	token;
	int		fd_infile;
	int		fd_outfile;

	fd_infile = -1;
	fd_outfile = -1;
	while (redir)
	{
		token = redir->content;
		if (token->type == TOKEN_REDIRECT_IN)
			fd_infile = close_or_assign(fd_infile, redir_in(token));
		else if (token->type == TOKEN_REDIRECT_OUT)
			fd_outfile = close_or_assign(fd_outfile, redir_out(token));
		else if (token->type == TOKEN_REDIRECT_OUT_APPEND)
			fd_outfile = close_or_assign(fd_outfile, redir_append(token));
		else if (token->type & TOKEN_HERE_DOCUMENT)
			fd_infile = close_or_assign(fd_infile, token->fd);
		if (fd_infile == -2 || fd_outfile == -2)
			return (close_all(redir, fd_infile, fd_outfile), 1);
		redir = redir->next;
	}
	pipex->infile = fd_infile;
	pipex->outfile = fd_outfile;
	return (0);
}

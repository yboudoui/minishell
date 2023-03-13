/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:13:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/13 17:46:34 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int redir_in(t_token token)
{
	int	fd;

	fd = f_open((char *)token->input, O_RDONLY, 0);
	return (fd);
}

int redir_out(t_token token)
{
	int	fd;

	fd = f_open((char *)token->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int redir_append(t_token token)
{
	int	fd;

	fd = f_open((char *)token->input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int close_or_assign(int fd_end, int fd_new)
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

int close_all(t_list redir, int fd_infile, int fd_outfile)
{
	t_token	token;
	close_fd(&fd_infile);
	close_fd(&fd_outfile);
	while (redir)
	{
		token = redir->content;
		if (token->type == TOKEN_HERE_DOCUMENT)
			close_fd((int *)token->input);
		redir = redir->next;
	}
	return (1);
}

int manage_redirs(t_list redir, t_pipex *pipex)
{
	t_token	token;
	int fd_infile;
	int fd_outfile;

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
		else if (token->type == TOKEN_HERE_DOCUMENT)
			fd_infile = close_or_assign(fd_infile, *(int *)(token->input));
		if (fd_infile == -2 || fd_outfile == -2)
		{
			close_all(redir, fd_infile, fd_outfile);
			return (1);
		}
		redir = redir->next;
	}
	pipex->infile = fd_infile;
	pipex->outfile = fd_outfile;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:38:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/20 14:15:44 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "minishell.h"

static void	heredoc_error(char *stop_word)
{
	g_global.exit_code = 0;
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(stop_word, 2);
	ft_putstr_fd("')\n", 2);
}

static bool	heredoc_stop(char **line, char *stop_word)
{
	char	*_read;

	if (line == NULL || stop_word == NULL)
		return (false);
	_read = readline("> ");
	if (_read == NULL && g_global.exit_code != 130)
		return (heredoc_error(stop_word), false);
	if (_read && string_cmp(_read, stop_word) == 0)
		return (free(_read), false);
	(*line) = _read;
	return (true);
}

int	heredoc_read(t_token token)
{
	int		fds[2];
	char	*line;
	bool	expand;

	if (token == NULL || pipe(fds))
		return (EXIT_FAILURE);
	expand = !(token->type & TOKEN_QUOTE);
	g_global.exit_code = 0;
	while (heredoc_stop(&line, token->input))
	{
		if (g_global.exit_code)
		{
			close_fd(&fds[0]);
			close_fd(&fds[1]);
			return (free(line), false);
		}
		if (expand)
			env_find_and_expand_var_to(&line);
		ft_putnl_fd(line, fds[1]);
		free(line);
	}
	token->fd = fds[0];
	return (close_fd(&fds[1]), true);
}

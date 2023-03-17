/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:38:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 09:41:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "minishell.h"

static const char	*g_heredoc_error_msg = "warning:"
	"here-document at line 1 delimited by end-of-file (wanted `%s')\n";

static bool	heredoc_stop(char **line, char *stop_word)
{
	char	*_read;

	if (line == NULL || stop_word == NULL)
		return (false);
	_read = readline("> ");
	if (_read && string_cmp(_read, stop_word) == 0)
		return (free(_read), false);
	(*line) = _read;
	return (true);
}

static bool	have_to_expand(t_token token)
{
	char	*str;
	char	*new;

	if (token == NULL || token->input == NULL)
		return (false);
	new = NULL;
	str = token->input;
	if (str[0] == '"')
		new = ft_strtrim(str, "\"");
	if (str[0] == '\'')
		new = ft_strtrim(str, "'");
	if (new == NULL)
		return (true);
	free (token->input);
	token->input = new;
	return (false);
}

int	heredoc_read(t_token token)
{
	int		fds[2];
	char	*line;
	bool	expand;

	if (token == NULL || pipe(fds))
		return (EXIT_FAILURE);
	expand = have_to_expand(token);
	while (heredoc_stop(&line, token->input))
	{
		if (g_global.exit_code || line == NULL)
		{
			close_fd(&fds[0]);
			close_fd(&fds[1]);
			if (g_global.exit_code != 130)
				printf(g_heredoc_error_msg, token->input);
			return (false);
		}
		if (expand)
			env_find_and_expand_var(&line);
		ft_putnl_fd(line, fds[1]);
		free(line);
	}
	token->fd = fds[0];
	return (close_fd(&fds[1]), EXIT_SUCCESS);
}

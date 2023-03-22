/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:38:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 15:41:35 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "minishell.h"

static void	heredoc_error(char *stop_word)
{
	char	**fmt;
	char	*error;

	g_global.exit_code = 0;
	fmt = (char *[]){
		"here-document delimited by end-of-file (wanted `", stop_word, "')\n",
		NULL};
	error = str_join_list(fmt, NULL);
	generic_err("warning", error, 2);
	free(error);
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

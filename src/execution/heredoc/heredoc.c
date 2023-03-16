/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:05:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/16 19:00:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "minishell.h"
#include <unistd.h>

void	signal_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
//	write(STDERR_FILENO, "\n", 1); // sortie d'erreur!!!
	close(STDIN_FILENO);
	g_global.exit_code = 130;
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

static int	heredoc_read(t_token token)
{
	int		fds[2];
	int		*new;
	char	*line;
	char	*expanded;
	bool	expand;

	if (token == NULL)
		return (EXIT_SUCCESS);
	if (pipe(fds))
		return (EXIT_FAILURE);
	new = ft_calloc(1, sizeof(int));
	if (new == NULL)
		return (EXIT_FAILURE);
	(*new) = fds[0];
	expand = have_to_expand(token);
	str_new_empty(&line);
	g_global.exit_code = 0;
	while (line)
	{
		free(line);
		line = readline("> ");
		if (g_global.exit_code || line == NULL)
		{
			close_fd(&fds[0]);
			close_fd(&fds[1]);
			printf("warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", (char *)token->input);
			free(token->input);
			token->input = new;
			return (EXIT_FAILURE);
		}
		if (string_cmp(line, token->input) == 0)
			break ;
		if (!is_empty(line))
			add_history(line);
		if (expand)
		{
			expanded = env_find_and_expand_var(line);
			if (expanded)
			{
				write(fds[1], expanded, ft_strlen(expanded));
				free(expanded);
			}
			else
				write(fds[1], line, ft_strlen(line));
		}
		else
			write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
	}
	free(token->input);
	token->input = new;
	return (close_fd(&fds[1]), EXIT_SUCCESS);
}

static int	heredoc_commande(t_commande cmd)
{
	t_token_list	redir;
	int				*last;

	last = NULL;
	redir = (t_token_list)cmd->redir;
	while (redir)
	{
		if (redir->token->type == TOKEN_HERE_DOCUMENT)
		{
			if (last)
				close_fd(last);
			if (heredoc_read(redir->token))
				return (EXIT_FAILURE);
			last = redir->token->input;
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_prompt cmd)
{
//	struct sigaction		old;
	const struct sigaction	sigint = {
		.sa_handler = signal_control_c,
		.sa_flags = SA_RESETHAND
	};

	g_global.save_stdin = dup(STDIN_FILENO);
	sigaction(SIGINT, &sigint, NULL);//&old);
	while (cmd)
	{
		if (heredoc_commande(cmd->content))
		{
			dup2(g_global.save_stdin, STDIN_FILENO);
			close(g_global.save_stdin);
			return (EXIT_FAILURE);
		}
		cmd = cmd->next;
	}
	close(STDIN_FILENO);
	dup2(g_global.save_stdin, STDIN_FILENO);
	close(g_global.save_stdin);
//	sigemptyset()
//	sigaction(SIGINT, &old, NULL);
	return (EXIT_SUCCESS);
}

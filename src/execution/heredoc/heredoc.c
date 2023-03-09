/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:05:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/09 16:48:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "../../../inc/minishell.h"

int	g_stop = 0;

void	signal_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDERR_FILENO, "\n", 1); // sortie d'erreur!!!
	close(STDIN_FILENO);
	g_stop = 1;
}

static int	heredoc_read(t_token token)
{
	int		fds[2];
	int		*new;
	char	*line;
	char	*expanded;
	bool	expand;

	if (token->type != TOKEN_HERE_DOCUMENT)
		return (EXIT_SUCCESS);
	str_new_empty(&line);
	if (pipe(fds))
		return (EXIT_FAILURE);
	new = ft_calloc(1, sizeof(int));
	if (new == NULL)
		return (EXIT_FAILURE);
	(*new) = fds[0];
	expand = (((char *)token->input)[0] != '"' &&  ((char *)token->input)[0] != '\'');
	if (expand)
	{
		line = ft_strtrim((char *)token->input, "\"'");
		free(token->input);
		token->input = line;
	}
	str_new_empty(&line);
	while (line)
	{
		free(line);
		line = readline("> ");
		if (g_stop || line == NULL)
		{
			/* close(fds[0]); */
			close(fds[1]);
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
			write(fds[1], expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
			write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
	}
	free(token->input);
	token->input = new;
	return (close(fds[1]), EXIT_SUCCESS);
}

static int	heredoc_commande(t_commande cmd)
{
	t_list	redir_in;

	redir_in = cmd->redir_in;
	while (redir_in)
	{
		if (heredoc_read(redir_in->content))
			return (EXIT_FAILURE);
		redir_in = redir_in->next;
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_prompt cmd)
{
	const struct sigaction	sigint = {
		.sa_handler = signal_control_c
	};
	struct sigaction	old;

	sigaction(SIGINT, &sigint, &old);
	while (cmd)
	{
		if (heredoc_commande(cmd->content))
			return (EXIT_FAILURE);
		cmd = cmd->next;
	}
	sigaction(SIGINT, &old, NULL);
	return (EXIT_FAILURE);
}

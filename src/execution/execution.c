/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/07 07:17:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Warning!!!
	How to handle the the PID of the scrip?
	example:
		echo $$
	source:
		[Advanced Bash-Scripting Guide: Internal Variables]
		(https://tldp.org/LDP/abs/html/internalvariables.html#PROCCID)
*/

static char	*extract_variable(char **str)
{
	char	*out;
	int		index;

	index = 0;
	if ((*str)[index] != '$')
		return ((*str)++, NULL);
	index += 1;
	while ((*str)[index] || (*str)[index] == '$' || is_space((*str)[index]))
		index++;
	out = ft_substr(*str, 1, index);
	(*str) += index;
	return (out);
}

static char	*str_extract_remaining(char **str, size_t *index)
{
	char	*out;

	if (!str || !index)
		return (NULL);
	out = ft_substr(*str, 0, *index);
	(*str) += (*index);
	(*index) = 0;
	return (out);
}

char	*find_and_expand_variable(char *str)
{
	char	*out;
	char	*remaining;
	char	*variable_found;
	size_t	index;

	str_new_empty(&out);
	index = 0;
	while (*str)
	{
		variable_found = extract_variable(&str);
		if (variable_found)
		{
			remaining = str_extract_remaining(&str, &index);
			out = str_merge(out, remaining, env_get_value(variable_found), NULL);
		}
		else
			index++;
	}
	if (!ft_strlen(out))
		return (free(out), NULL);
	return (out);
}

static void	find_and_expand_env_var(void *token, void *_)
{
	t_token		tk;
	char		*output;
	size_t		old;
	size_t		range[2];

	(void)_;
	tk = token;
	if (tk == NULL)
		return ;
	str_new_empty(&output);
	old = 0;
	while (bash_definition_name(range, tk->input))
	{
		output = str_merge_list((char *[]){output,
				ft_substr(tk->input, old, range[0]),
				ft_substr(tk->input, range[0], range[1]),
				NULL
			});
	}
	free(tk->input);
	tk->input = output;
}

static void	commande_expand_variable(void *commande, void *_)
{
	t_commande	cmd;

	(void)_;
	cmd = commande;
	if (cmd == NULL)
		return ;
	list_iter(cmd->argv, find_and_expand_env_var, NULL);
	list_iter(cmd->redir_in, find_and_expand_env_var, NULL);
	list_iter(cmd->redir_out, find_and_expand_env_var, NULL);
}

int	execution(t_prompt prompt)
{
	if (prompt == NULL)
		return (EXIT_FAILURE);
	if (!heredoc(prompt))
		return (EXIT_FAILURE);
	list_iter(prompt, commande_expand_variable, NULL);
	pipex(prompt);
	return (EXIT_SUCCESS);
}

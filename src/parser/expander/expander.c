/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:35:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 09:56:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

char	*expand_variable(t_list env, char *var_name)
{
	t_env_var	var;

	while (env)
	{
		var = env->content;
		if (ft_strncmp(var->name, var_name, ft_strlen(var->name)) == 0)
			return (ft_strdup(var->value));
		env = env->next;
	}
	return (ft_strdup("\0"));
}

static char	*find_and_expand_variable(t_list env, char *str)
{
	char	*out;
	char	*remaining;
	char	*variable_found;
	size_t	index;

	out = ft_strdup("\0");
	index = 0;
	while (*str)
	{
		variable_found = extract_variable(&str);
		if (variable_found)
		{
			remaining = str_extract_remaining(&str, &index);
			out = str_merge(out, remaining,
					expand_variable(env, variable_found), NULL);
			free(variable_found);
		}
		else
			index++;
	}
	if (!ft_strlen(out))
		return (free(out), NULL);
	return (out);
}

void	list_find_and_expand_variable(t_list env, t_list token)
{
	t_token	cast;
	char	*new;

	while (token)
	{
		cast = token->content;
		new = find_and_expand_variable(env, cast->input);
		if (new)
		{
			free(cast->input);
			cast->input = new;
		}
		token = token->next;
	}
}

void	commande_expand_variable(t_list env, t_commande cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->argv)
		list_find_and_expand_variable(env, cmd->argv);
	if (cmd->redir_in)
		list_find_and_expand_variable(env, cmd->redir_in);
	if (cmd->redir_out)
		list_find_and_expand_variable(env, cmd->redir_out);
	if (cmd->redir_out_append)
		list_find_and_expand_variable(env, cmd->redir_out_append);
}

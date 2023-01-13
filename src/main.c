/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 08:36:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "prompt.h"

#include "show.h"

// juste for test
#include "expander.h"

void	expand_all_command(t_list env, t_list cmd)
{
	while (cmd)
	{
		commande_expand_variable(env, cmd->content);
		cmd = cmd->next;
	}
}

void	exe(t_list env, t_prompt prompt)
{
	(void)env;
	if (prompt == NULL)
		return ;
	if (prompt->commande == NULL)
		return ;
	ft_lstiter(prompt->commande, print_commande_line);
	expand_all_command(env, prompt->commande);
	ft_lstiter(prompt->commande, print_commande_line);
}

int	execution(char *env[], void (*exec)(t_list, t_prompt))
{
	t_list		env_list;
	char		*line;
	t_prompt	prompt;

	env_list = environment_list_create(env);
	while (1)
	{
		rl_on_new_line();
		line = readline("~$ ");
		if (line == NULL)
			break ;
		if (!is_empty(line))
			add_history(line);
		prompt = prompt_create(line);
		exec(env_list, prompt);
		prompt_destroy(prompt);
		free(line);
	}
	rl_clear_history();
	environment_list_destroy(env_list);
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	return (execution(env, exe));
}

/*
ls $HOME | cat main.c >> $USER < $LANG<$LOGNAME|             ls $SHELL -la > here|grep $LESS
*/

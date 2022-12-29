/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/29 17:59:22 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "utils.h"

#include "lexer.h"
#include "show.h"
#include <readline/readline.h>
#include <readline/history.h>

void	parsing(char *input)
{
	t_list	lexer_output;

	lexer_output = NULL;
	lexer(input, &lexer_output);
	print_lexer_output(lexer_output);
	list_clear(&lexer_output, token_destroy);
}

int	main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		rl_on_new_line();
		line = readline("~$ ");
		if (NULL == line)
			break ;
		add_history(line);
		parsing(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}

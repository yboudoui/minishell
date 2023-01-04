/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:32:38 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/01 14:24:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "read_line.h"

void	readline_handler(bool (*handler)(char *))
{
	char	*line;

	while (1)
	{
		rl_on_new_line();
		line = readline("~$ ");
		if (NULL == line)
			break ;
		add_history(line);
		handler(line);
		free(line);
	}
	rl_clear_history();
}

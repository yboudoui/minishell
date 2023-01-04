/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/30 14:58:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "read_line.h"

bool	parsing(char *input)
{
	if (!lexer_handler(input))
		return (true);
	return (false);
}

int	main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	(void)env;
	readline_handler(parsing);
	return (0);
}

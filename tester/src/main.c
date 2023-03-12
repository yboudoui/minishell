/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 06:28:08 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/12 14:03:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiplexer.h"

int	main(int ac, char *av[], char *env[])
{
	t_multiplexer	ml;

	(void)ac;
	(void)av;

	ml = multiplexer_create(env, "/bin/bash", "../minishell");

	multiplexer_write(ml, "ls\n");
//	multiplexer_write(ml, "lol\n");

	multiplexer_destroy(ml);
	return (0);
}

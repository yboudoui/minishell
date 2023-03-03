/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:59:20 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 19:28:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(char *argv[], t_env_list *env)
{
	(void)argv;
	(void)env;
	printf("exit\n");
	return (EXIT_SUCCESS);
}

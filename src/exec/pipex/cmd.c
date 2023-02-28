/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:51:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/28 19:10:27 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int exec_cmd(t_pipex *pipex, char **argv, int in, int out)
{
	char *cmd_path;

	dup_fd(in, STDIN_FILENO);
	dup_fd(out, STDOUT_FILENO);
	cmd_path = get_cmd_path(pipex, argv[0]);
	/* printf("cmd_path = %s\n", cmd_path); */
	/* while (argv && *argv) */
	/* 	printf("argv = %s\n", *argv++); */
	if (cmd_path == NULL)
		return (EXIT_FAILURE);
	execve(cmd_path, argv, parse_env(pipex->env));
	return (-1);
}

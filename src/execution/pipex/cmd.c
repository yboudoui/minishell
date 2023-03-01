/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:51:18 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/28 20:40:03 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int exec_cmd(t_pipex *pipex, char **argv, int in, int out)
{
	char *cmd_path;

	if (dup2(in, STDIN_FILENO) == -1)
		generic_err("dup2", NULL, 1);
	if (dup2(out, STDOUT_FILENO) == -1)
		generic_err("dup2", NULL, 1);
	cmd_path = get_cmd_path(pipex, argv[0]);
	if (cmd_path == NULL)
		return (EXIT_FAILURE);
	if (execve(cmd_path, argv, parse_env(pipex->env)) == -1)
		generic_err("execve", NULL, 1);
	return (-1);
}

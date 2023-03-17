/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:33:35 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/17 18:58:22 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
/*
static void	signal_control_c(int sig)
{
	(void)sig;
	printf("l\n");
//	if (sig != SIGINT)
//		return ;
	write(STDERR_FILENO, "9\n", 2);
//	close(STDIN_FILENO);
	g_global.exit_code = 130;
}
*/
static const struct sigaction	g_default_sig[2] = {
	{.sa_handler = SIG_DFL},
	{.sa_handler = SIG_IGN}
};

int	execute(char *argv[], t_pipex *pipex)
{
	pipe_fd(pipex, pipex->fd);
	if (argv != NULL && !pipex->redir_error)
		pipex->cmd_path = get_cmd_path(pipex, argv[0]);
	if (pipex->cmd_path == NULL)
		pipex->exitcode = CMD_NOT_FOUND;
	sigaction(SIGINT, &g_default_sig[1], NULL);
	sigaction(SIGQUIT, &g_default_sig[1], NULL);
	fork_pid(&pipex->pid[pipex->i]);
	if (pipex->pid[pipex->i] == 0)
	{
		sigaction(SIGINT, &g_default_sig[0], NULL);
		sigaction(SIGQUIT, &g_default_sig[0], NULL);
		exec_cmd(pipex, argv);
	}
	dup_fd(pipex->fd[0], STDIN_FILENO);
	close_fd(&pipex->fd[1]);
	close_fd(&pipex->fd[0]);
	close_fd(&pipex->infile);
	close_fd(&pipex->outfile);
	f_free((void **)&pipex->cmd_path);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/12 15:24:45 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	init_exec(t_pipex *pipex)
{
	pipex->pid = ft_calloc(pipex->argc, sizeof(pid_t));
	if (pipex->pid == NULL)
		return (generic_err("malloc", NULL, 2), -1);
	return (0);
}

int	waitall(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->argc)
	{
		waitpid(pipex->pid[i], &pipex->status, 0);
		i++;
	}
	if (WIFSIGNALED(pipex->status))
	{
		if (WTERMSIG(pipex->status) == 2)
		{
			g_global.exit_code = 130;
			ft_putstr_fd("\n", 1);
		}
		if (WTERMSIG(pipex->status) == 3)
		{
			g_global.exit_code = 131;
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
	}
	else if (WIFEXITED(pipex->status))
		g_global.exit_code = WEXITSTATUS(pipex->status);
	/* signal(SIGINT, SIG_DFL); */
	/* signal(SIGQUIT, SIG_DFL); */
	return (0);
}

int	reset_flags(t_pipex *pipex)
{
	pipex->abs_path_cmd = false;
	pipex->builtin = NULL;
	return (0);
}

int free_pipex(void)
{

	if (g_global.pipex == NULL)
		return (-1);
	dup_fd(g_global.pipex->stdin_fd, STDIN_FILENO);
	close_fd(&g_global.pipex->stdin_fd);
	if (g_global.pipex->infile > 2)
		close_fd(&g_global.pipex->infile);
	if (g_global.pipex->outfile > 2)
		close_fd(&g_global.pipex->outfile);
	free(g_global.pipex->pid);
	string_array_destroy(g_global.pipex->paths);
	g_global.pipex->paths = NULL;
	free(g_global.pipex);
	return (0);
}

int	pipex(t_cmd_list cmds)
{
	t_pipex			*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	g_global.pipex = pipex;
	pipex->argc = list_size((t_list)cmds);
	pipex->builtin = NULL;
	if (pipex->argc == 1 && cmds->cmd->argv)
	{
		pipex->builtin = is_builtin(cmds->cmd->argv[0]);
		if (pipex->builtin)
		{
			run_builtin(pipex, cmds->cmd->argv);
			return (0);
		}
	}
	pipex->stdin_fd = dup(STDIN_FILENO);
	pipex->paths = get_paths(pipex);
	pipex->env = env_list_singleton(NULL);
	if (init_exec(pipex) == -1)
		return (EXIT_FAILURE);
	while (cmds)
	{
		reset_flags(pipex);
		pipex->redir_error = manage_redirs(cmds->cmd->redir, pipex);
		printf("redir_error = %d\n", pipex->redir_error);
		execute(cmds->cmd->argv, pipex);
		cmds = cmds->next;
		printf("loop %d\n", pipex->i);
		pipex->i++;
	}
	waitall(pipex);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_control_c_);
	free_pipex();
	return (0);
}

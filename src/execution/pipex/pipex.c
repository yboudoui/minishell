/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/11 15:18:35 by kdhrif           ###   ########.fr       */
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
			ft_putstr_fd("\n", 1);
		if (WTERMSIG(pipex->status) == 3)
			ft_putstr_fd("Quit (core dumped)\n", 1);
	}
	else if (WIFEXITED(pipex->status))
		g_global.exit_code = WEXITSTATUS(pipex->status);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	free(g_global.pipex->pid);
	string_array_destroy(g_global.pipex->paths);
	g_global.pipex->paths = NULL;
	g_global.pipex = NULL;
	return (0);
}

bool	is_there_a_commande(t_prompt prompt)
{
	while (prompt)
	{
		if (prompt->content && prompt->content->argv)
			return (true);
		prompt = prompt->next;
	}
	return (false);
}

int	pipex(t_cmd_list cmds)
{
	t_pipex					pipex;
	static const t_pipex	empty_pipex;
	int						error_code;

	g_global.pipex = &pipex;
	error_code = EXIT_SUCCESS;
	pipex = empty_pipex;
	pipex.argc = list_size((t_list)cmds);
	pipex.builtin = NULL;
	if (pipex.argc == 1 && cmds->cmd->argv)
	{
		pipex.builtin = is_builtin(cmds->cmd->argv[0]);
		if (pipex.builtin)
		{
			run_builtin(&pipex, cmds->cmd->argv);
			return (0);
		}
	}
	pipex.stdin_fd = dup(STDIN_FILENO);
	pipex.paths = get_paths(&pipex);
	pipex.env = env_list_singleton(NULL);
	if (init_exec(&pipex) == -1)
		return (EXIT_FAILURE);
	while (cmds)
	{
		reset_flags(&pipex);
		pipex.redir_error = manage_redirs(cmds->cmd->redir, &pipex);
		if (cmds->cmd->argv == NULL)
		{
			close_fd(&pipex.infile);
			close_fd(&pipex.outfile);
		}
		else if (execute(cmds->cmd->argv, &pipex))
			error_code = EXIT_FAILURE;
		cmds = cmds->next;
		pipex.i++;
	}
	waitall(&pipex);
//	signal(SIGQUIT, SIG_IGN);
//	signal(SIGINT, signal_control_c_);
	free_pipex();
	return (error_code);
}

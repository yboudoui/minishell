/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 16:12:34 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

t_global	g_global;

void	signal_control_c_(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDIN_FILENO, "\n", 1);
	g_global.exit_code = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	execution(t_prompt prompt)
{
	t_cmd_list	cmd;

	if (g_global.prompt == NULL)
		return (EXIT_FAILURE);
	if (heredoc(prompt))
		return (EXIT_SUCCESS);
	list_iter(prompt, commande_expand_variable, NULL);
	cmd = convertion(prompt);
	g_global.cmds = cmd;
	pipex(cmd);
	cmd_list_destroy(&g_global.cmds);
	return (EXIT_SUCCESS);
}

static int	read_prompt(void)
{
	char					*line;
	const struct sigaction	signals[2] = {
	{.sa_handler = signal_control_c_},
	{.sa_handler = SIG_IGN}
	};

	incr_shlvl();
	while (42)
	{
		sigaction(SIGINT, &signals[0], &g_global.default_sigint);
		sigaction(SIGQUIT, &signals[1], &g_global.default_sigquit);
		line = readline("~$> ");
		if (line == NULL)
			return (printf("exit\n"), EXIT_FAILURE);
		if (!is_empty(line))
		{
			add_history(line);
			g_global.prompt = prompt_create(line);
			execution(g_global.prompt);
			prompt_destroy(&g_global.prompt);
		}
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

int	loop_tester(char *line)
{
	g_global.prompt = prompt_create(line);
	execution(g_global.prompt);
	prompt_destroy(&g_global.prompt);
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	(void)av;
	g_global = (t_global){0};
	if (ac != 1 || isatty(STDIN_FILENO) == 0)
		return (EXIT_FAILURE);
	if (!env_list_create(envp))
		return (-1);
	if (ac >= 2)
	{
		if (av[1][0] == '-' && av[1][1] == 'c' && av[2])
			loop_tester(av[2]);
		else
			generic_err(av[1], "No such file or directory\n", 2);
		return (g_global.exit_code);
	}
	read_prompt();
	return (meta_exit(g_global.exit_code, NULL), EXIT_SUCCESS);
}

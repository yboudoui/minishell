/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/16 19:00:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>

t_global	g_global;

void	signal_control_c_(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	read_prompt(void)
{
	const struct sigaction	signals[2] = {
	{.sa_handler = signal_control_c_},
	{.sa_handler = SIG_IGN}
	};
	char		*line;

	incr_shlvl();
	while (42)
	{
		sigaction(SIGINT, &signals[0], &g_global.default_sigint);
		sigaction(SIGQUIT, &signals[1], &g_global.default_sigquit);
		line = readline("~$> ");
		if (line == NULL)
			return (EXIT_FAILURE);
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

int	main(int ac, char *av[], char *envp[])
{
	(void)av;
	g_global = (t_global){0};
	if (ac != 1 || !isatty(ttyslot()))
		return (EXIT_FAILURE);
	if (!env_list_create(envp))
		return (-1);
	read_prompt();
	return (meta_exit(0, NULL), EXIT_SUCCESS);
}

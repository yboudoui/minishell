/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/07 12:13:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_code;

static void	signal_control_c(int sig)
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
	char		*line;
	int			exe_stop;
	t_prompt	prompt;

	exe_stop = 0;
	while (!exe_stop)
	{
		line = readline("~$ ");
		if (line == NULL)
			return (EXIT_FAILURE);
		if (!is_empty(line))
		{
			add_history(line);
			prompt = prompt_create(line);
			exe_stop = execution(prompt);
			prompt_destroy(prompt);
		}
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[], char *envp[])
{
	const struct sigaction	signals[2] = {
	{.sa_handler = signal_control_c},
	{.sa_handler = SIG_IGN}
	};

	(void)av;
	g_exit_code = 0;
	rl_outstream = stderr;
	if (ac != 1 || !isatty(ttyslot()))
		return (EXIT_FAILURE);
	sigaction(SIGINT, &signals[0], NULL);
	sigaction(SIGQUIT, &signals[1], NULL);
	if (!env_list_create(envp))
		return (-1);
	read_prompt();
	env_list_destroy();
	return (EXIT_SUCCESS);
}

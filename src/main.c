/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:04:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 15:58:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	read_prompt(t_env_list env)
{
	char		*line;
	int			exe_stop;
	t_prompt	prompt;

	exe_stop = 0;
	while (!exe_stop)
	{
		rl_on_new_line();
		line = readline("~$ ");
		if (!line)
			return (EXIT_SUCCESS);	// maybe not a good idea
		if (!is_empty(line))
		{
			add_history(line);
			prompt = prompt_create(line);
			exe_stop = execution(env, prompt);
			prompt_destroy(prompt);
		}
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[], char *envp[])
{
	t_env_list				env;
	const struct sigaction	signals[2] = {
	{.sa_handler = signal_control_c},
	{.sa_handler = SIG_IGN}
	};

	(void)av;
	if (ac != 1 || !isatty(ttyslot()))
		return (EXIT_FAILURE);
	sigaction(SIGINT, &signals[0], NULL);
	sigaction(SIGQUIT, &signals[1], NULL);
	env = environment_list_create(envp);
	read_prompt(env);
	environment_list_destroy(env);
	return (EXIT_SUCCESS);
}

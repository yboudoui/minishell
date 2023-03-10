/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:12:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/10 17:40:45 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../show/show.h"
# include "../inc/utils/string.h"
# include "../inc/utils/list.h"
# include "../inc/utils/memory.h"
# include "../inc/parser/prompt/commande/commande.h"
# include "../inc/parser/prompt/prompt.h"
# include "../inc/parser/token.h"
# include "../inc/parser/environment/environment.h"
# include "../inc/execution/builtin/builtin.h"
# include "../inc/execution/pipex/exec.h"
# include "../inc/execution/heredoc/heredoc.h"
# include "../inc/execution/cmd.h"

# include <stdbool.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

void	signal_control_c_(int sig);

typedef struct s_global {
	int					exit_code;
	struct sigaction	default_sigint;
	struct sigaction	default_sigquit;
	t_prompt			prompt;
	t_cmd_list			cmds;
	t_pipex				*pipex;
}	t_global;

extern t_global	g_global;

void	meta_exit(int exitcode);
int		execution(t_prompt prompt);

#endif

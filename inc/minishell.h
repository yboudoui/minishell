/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:12:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/22 15:39:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <limits.h>
# include <signal.h>

void	signal_control_c_(int sig);

typedef struct s_global {
	int					exit_code;
	int					heredoc_signal;
	struct sigaction	default_sigint;
	struct sigaction	default_sigquit;
	t_prompt			prompt;
	t_cmd_list			cmds;
	int					save_stdin;
	t_pipex				*pipex;
}	t_global;

extern t_global	g_global;

void	commande_expand_variable(void *commande, void *_);
void	meta_exit(int exitcode, t_pipex *pipex);
void	incr_shlvl(void);

#endif

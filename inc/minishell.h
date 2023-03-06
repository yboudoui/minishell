/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:12:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 18:33:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../show/show.h"
# include "../inc/utils/string/string.h"
# include "../inc/utils/list/list.h"
# include "../inc/utils/utils.h"
# include "../inc/utils/memory/memory.h"
# include "../inc/parser/prompt/commande/commande.h"
# include "../inc/parser/prompt/prompt.h"
# include "../inc/parser/token.h"
# include "../inc/parser/environment/environment.h"
# include "../inc/execution/pipex/exec.h"
# include "../inc/execution/heredoc/heredoc.h"
# include "../inc/execution/cmd.h"

# include "builtin.h"

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

extern int	g_exit_code;

bool	bash_definition_name(size_t range[2], char *str);
char	*find_bash_definition_name(const char *str);
char	*find_bash_definition_variable(const char *str);
int		execution(t_prompt prompt);

#endif

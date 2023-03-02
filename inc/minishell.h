/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:12:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 15:57:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../show/show.h"
# include "../inc/utils/string/string.h"
# include "../inc/utils/list/list.h"
# include "../inc/utils/utils.h"
# include "../inc/utils/memory/memory.h"
# include "../inc/parser/syntaxer.h"
# include "../inc/parser/prompt/commande/commande.h"
# include "../inc/parser/prompt/prompt.h"
# include "../inc/parser/lexer/modules.h"
# include "../inc/parser/lexer/token.h"
# include "../inc/parser/lexer/lexer.h"
# include "../inc/parser/expander/expander.h"
# include "../inc/parser/environment/environment.h"
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

int	execution(t_env_list env, t_prompt prompt);

#endif

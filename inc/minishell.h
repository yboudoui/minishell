/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:12:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 16:30:13 by kdhrif           ###   ########.fr       */
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
# include "../inc/exec/exec.h"
# include "../inc/heredoc/heredoc.h"

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

typedef struct s_prompt	*t_prompt;

//typedef struct s_cmd t_cmd;
/* struct s_cmd { */
/* 	char**	argv; */
/* 	t_list	redir_in; //content can be casted as char * */
/* 	t_list	redir_out; //content can be casted as char * */
/* 	char*	here_document; // need to wait for it to be done */
/* }; */

/* typedef struct s_list_commande { */
/* 	t_commande	content; */
/* 	struct s_list_commande	*next; */
/* 	struct s_list_commande	*prev; */
/* }	*t_list_commande; */


int	execution(t_list env, t_prompt prompt);

#endif

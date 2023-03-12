/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:46:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/11 17:19:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLEXER_H
# define MULTIPLEXER_H

#include "shell.h"

typedef enum e_shell_kind {
	B_SH,
	M_SH,
	MAX_SH,
}	t_shell_kind;

typedef struct s_multiplexer	*t_multiplexer;

struct s_multiplexer {
	t_shell	sh[MAX_SH];
};

t_multiplexer	multiplexer_create(char *env[], char *bash, char *minishell);
void			multiplexer_write(t_multiplexer ml, char *cmd);
void			multiplexer_destroy(t_multiplexer ml);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:15:14 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/11 15:55:59 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "lexer.h"
# include "syntaxer.h"

# include "commande.h"
# include "environment.h"

typedef struct s_prompt	*t_prompt;

struct s_prompt {
	t_list	heredoc;
	t_list	commande;
};

t_prompt	prompt_create(char *input);
void		prompt_destroy(void *input);

#endif

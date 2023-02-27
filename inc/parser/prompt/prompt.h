/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:15:53 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 15:15:57 by yboudoui         ###   ########.fr       */
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
	t_commande	content;
	t_prompt	next;
	t_prompt	prev;
};

typedef struct s_list_commande {
	t_commande	content;
	struct s_list_commande	*next;
	struct s_list_commande	*prev;
}	*t_list_commande;

t_prompt	prompt_create(char *input);
void		prompt_destroy(void *input);

#endif

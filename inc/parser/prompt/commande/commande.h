/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:16:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/22 15:53:29 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDE_H
# define COMMANDE_H

# include "list.h"
# include "token.h"

typedef struct s_commande	*t_commande;

struct s_commande {
	t_list	argv;
	t_list	redir_in;
	t_list	redir_out;
	t_list	redir_out_append;
	t_list	here_document;
};

t_commande	commande_create(t_list lst);
void		commande_destroy(void *data);

#endif

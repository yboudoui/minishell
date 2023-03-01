/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:15:01 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/01 13:13:03 by yboudoui         ###   ########.fr       */
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
	struct s_heredoc {
		t_list	list;
		int		*pipe;
	}	heredoc;
};

t_commande	commande_create(t_list lst);
void		commande_destroy(void *data);

#endif

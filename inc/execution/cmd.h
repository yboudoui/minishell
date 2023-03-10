/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:12:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/10 19:19:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "list.h"
# include "commande.h"
# include "prompt.h"

typedef struct s_cmd		*t_cmd;

struct s_cmd {
	char	**argv;
	t_list	redir_in;
	t_list	redir_out;
};

t_cmd		cmd_create(t_commande cmd);
void		cmd_destroy(void *data);

typedef struct s_cmd_list	*t_cmd_list;

struct s_cmd_list {
	t_cmd		cmd;
	t_cmd_list	next;
	t_cmd_list	prev;
};

t_cmd_list	convertion(t_prompt prompt);
void		cmd_list_destroy(void *data);
#endif

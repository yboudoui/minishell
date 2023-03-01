/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:12:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/01 14:22:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "list.h"
# include "commande.h"

typedef struct s_cmd	*t_cmd;

struct s_cmd {
	char	**argv;
	t_list	redir_in;
	t_list	redir_out;
};

t_cmd	cmd_create(t_commande cmd);
void	cmd_destroy(void *data);

#endif

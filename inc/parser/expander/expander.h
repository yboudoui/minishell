/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:39:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/26 12:53:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "environment.h"
# include "commande.h"

void	commande_expand_variable(t_list env, t_commande cmd);

#endif

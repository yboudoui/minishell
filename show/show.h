/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:10:39 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 18:43:36 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOW_H
# define SHOW_H

# include "list.h"
# include "utils.h"
# include "lexer.h"
# include <stdio.h>

void	print_error(char *str);
void	print_colored_token(void *content);
void	print_token_type(void *content);
const char	*get_token_type_string(t_token_type type);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:14:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/05 16:46:47 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "utils.h"
# include "token.h"

bool	token_match(char *str, t_list *output);
bool	token_list_sanitizer(t_list *lst);
bool	lexer_handler(char *input);

#endif

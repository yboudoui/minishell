/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:14:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/04 14:55:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "utils.h"
# include "token.h"

bool	token_match(char *str, t_list *output);
bool	token_list_sanitizer(t_list token_lst);
bool	lexer_handler(char *input);

#endif

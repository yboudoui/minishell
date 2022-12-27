/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modules.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 09:55:06 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 10:27:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULES_H
# define MODULES_H

# include "token.h"

t_token	token_is_spaces(char *str);

t_token	token_is_wildcard(char *str);
t_token	token_is_here_document(char *str);

t_token	token_is_redirect_in(char *str);
t_token	token_is_semicolon(char *str);

t_token	token_is_double_quote(char *str);
t_token	token_is_simple_quote(char *str);
t_token	token_is_subshell(char *str);

t_token	token_is_redirect_out_append(char *str);
t_token	token_is_redirect_out(char *str);

t_token	token_is_redirect_err_append(char *str);
t_token	token_is_redirect_err(char *str);

t_token	token_is_and(char *str);
t_token	token_is_background(char *str);

t_token	token_is_or(char *str);
t_token	token_is_pipe(char *str);

#endif

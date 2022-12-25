/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modules.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 09:55:06 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:33:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULES_H
# define MODULES_H

# include "token.h"

typedef t_token	(*t_fp_token_handler)(char **str);

t_token	is_redirect_in(char **str);
t_token	is_semicolon(char **str);

t_token	is_double_quote(char **str);
t_token	is_simple_quote(char **str);
t_token	is_subshell(char **str);

t_token	is_redirect_out_append(char **str);
t_token	is_redirect_out(char **str);

t_token	is_redirect_err_append(char **str);
t_token	is_redirect_err(char **str);

t_token	is_and(char **str);
t_token	is_background(char **str);

t_token	is_or(char **str);
t_token	is_pipe(char **str);

#endif

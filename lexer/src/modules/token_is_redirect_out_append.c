/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redirect_out_append.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:34:21 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:44:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_redirect_out_append(char *str)
{
	return (token_match(str, TOKEN_REDIRECT_OUT_APPEND, ">>", NULL));
}

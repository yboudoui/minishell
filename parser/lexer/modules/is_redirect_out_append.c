/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect_out_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:34:21 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 19:35:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	is_redirect_out_append(char **str)
{
	return (token_match(str, TOKEN_REDIRECT_OUT_APPEND, ">>", NULL));
}

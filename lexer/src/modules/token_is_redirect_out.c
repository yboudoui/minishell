/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redirect_out.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:35:20 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:44:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_redirect_out(char *str)
{
	return (token_match(str, TOKEN_REDIRECT_OUT, ">", NULL));
}

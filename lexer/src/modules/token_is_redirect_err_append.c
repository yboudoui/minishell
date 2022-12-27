/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redirect_err_append.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:38:27 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:44:29 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_redirect_err_append(char *str)
{
	return (token_match(str, TOKEN_REDIRECT_ERR_APPEND, "2>>", NULL));
}

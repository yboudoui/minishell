/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect_err_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:38:27 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 19:39:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	is_redirect_err_append(char **str)
{
	return (token_match(str, TOKEN_REDIRECT_ERR_APPEND, "2>>", NULL));
}

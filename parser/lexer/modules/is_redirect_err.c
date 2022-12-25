/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:56:28 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 20:03:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	is_redirect_err(char **str)
{
	return (token_match(str, TOKEN_REDIRECT_ERR, "2>", NULL));
}

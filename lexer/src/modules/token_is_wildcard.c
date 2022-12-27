/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:34:35 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:45:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_wildcard(char *str)
{
	return (token_match(str, TOKEN_WILDCARD, "*", NULL));
}

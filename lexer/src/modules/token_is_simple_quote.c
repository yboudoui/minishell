/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_simple_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:32:44 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:45:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_simple_quote(char *str)
{
	return (token_match(str, TOKEN_SIMPLE_QUOTES, "'", "'"));
}

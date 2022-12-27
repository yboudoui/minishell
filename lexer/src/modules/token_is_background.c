/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_background.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:01:06 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:41:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_background(char *str)
{
	return (token_match(str, TOKEN_BACKGROUND, "&", NULL));
}

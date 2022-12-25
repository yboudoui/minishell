/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_semicolon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:26:03 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 19:33:02 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	is_semicolon(char **str)
{
	return (token_match(str, TOKEN_SEMICOLON, ";", NULL));
}

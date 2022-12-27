/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_here_document.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:28:47 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/27 09:41:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules.h"

t_token	token_is_here_document(char *str)
{
	return (token_match(str, TOKEN_HERE_DOCUMENT, "<<", NULL));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:40:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/04 13:48:25 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

bool	is_alnum(char c)
{
	int	is_upper;
	int	is_lower;
	int	is_digit;

	is_upper = (c >= 'A' && c <= 'Z');
	is_lower = (c >= 'a' && c <= 'z');
	is_digit = (c >= '0' && c <= '9');
	return (is_upper || is_lower || is_digit);
}

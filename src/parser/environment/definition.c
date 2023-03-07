/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/07 09:25:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	bash_definition_name(char *str)
{
	int	index;

	index = 0;
	if (str == NULL || str[0] == '\0')
		return (-1);
	if (!str[index] || !is_alpha(str[index]) || str[index] != '_')
		return (-1);
	index += 1;
	while (str[index] && (is_alnum(str[index]) || str[index] == '_'))
		index += 1;
	return (index);
}

int	bash_definition_variable(char *str)
{
	int	index;

	index = 0;
	if (str == NULL || str[index] != '$')
		return (-1);
	index = bash_definition_name(str + 1);
	return (index + (index > 0));
}

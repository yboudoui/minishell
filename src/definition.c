/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:21:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 15:58:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef bool	(*t_fp_pattern)(size_t [2], char *);

typedef struct s_range {
	size_t	start;
	size_t	end;
}	t_range;

bool	bash_definition_name(size_t range[2], char *str)
{
	if (range == NULL || str == NULL)
		return (false);
	range[0] = 0;
	while ((!is_alpha(str[range[0]]) || str[range[0]] != '_') && str[range[0]])
		range[0] += 1;
	if (str[range[0]] == '\0')
		return (false);
	range[1] = range[0];
	while ((is_alnum(str[range[1]]) || str[range[1]] == '_') && str[range[1]])
		range[1] += 1;
	return (true);
}

char	*find_bash_definition_name(const char *str)
{
	size_t	index;

	if (str == NULL)
		return (NULL);
	index = 0;
	if (!is_alpha(str[index]) && str[index] != '_')
		return (NULL);
	index += 1;
	while (is_alnum(str[index]) || str[index] == '_')
		index += 1;
	return (ft_substr(str, 0, index));
}

char	*find_bash_definition_variable(const char *str)
{
	if (str == NULL)
		return (NULL);
	if (*str != '$')
		return (NULL);
	str += 1;
	return (find_bash_definition_name(str));
}

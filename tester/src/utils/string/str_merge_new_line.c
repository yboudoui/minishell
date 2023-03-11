/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_merge_new_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 07:26:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/27 07:27:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_merge_new_line(char *s1, char *s2)
{
	char	*output;
	char	*tmp;

	if (!is_empty(s1))
		output = ft_strjoin(s1, "\n");
	else
		output = ft_strdup("");
	tmp = output;
	output = ft_strjoin(tmp, s2);
	free(tmp);
	free(s1);
	free(s2);
	return (output);
}

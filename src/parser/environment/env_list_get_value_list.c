/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_get_value_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:30:56 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 14:27:32 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	**env_list_get_value_list(char *name)
{
	t_env_var	found;
	char		**output;
	size_t		index;

	if (name == NULL)
		return (NULL);
	found = env_find(name, 0, 0);
	if (found == NULL)
		return (NULL);
	output = ft_split(found->value, str_charset(":"));
	if (output == NULL)
		return (NULL);
	index = 0;
	while (output[index])
	{
		if (string_end_with(output[index], "/") == false)
			output[index] = str_merge_list((char *[]){
					output[index],
					ft_strdup("/"),
					NULL});
		index += 1;
	}
	return (output);
}

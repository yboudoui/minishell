/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:54:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/08 14:06:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	len = ((str_len > len) * len)
		+ ((str_len < len) * str_len)
		+ ((str_len == len) * (len - start));
	len = (!(start > str_len) * len);
	output = ft_calloc(len + 1, sizeof(char));
	if (output)
		ft_memcpy(output, s + start, len);
	return (output);
}

bool	ft_substr_to(char **out, char *in, unsigned int start, size_t len)
{
	(*out) = ft_substr(in, start, len);
	return (*out);
}

void	str_array_destroy(void *data)
{
	size_t	index;
	char	**input;

	input = data;
	if (input == NULL)
		return ;
	index = 0;
	while (input[index])
	{
		free(input[index]);
		index += 1;
	}
	free(input);
}

char	**ft_multi_substr(char const *input, size_t *ranges[])
{
	size_t	len;
	size_t	index;
	char	**output;

	len = sizeof_array(ranges, sizeof(size_t *), NULL);
	if (input == NULL || len == 0)
		return (NULL);
	output = ft_calloc(len + 1, sizeof(char *));
	index = 0;
	while (index < len)
	{
		output[index] = ft_substr(input, ranges[index][0], ranges[index][1]);
		if (output[index] == NULL)
			return (str_array_destroy(output), NULL);
		index += 1;
	}
	return (output);
}

bool	ft_multi_substr_to(char ***output, char *input, size_t *ranges[])
{
	(*output) = ft_multi_substr(input, ranges);
	return (*output);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:46:09 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 10:41:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static size_t	ft_is_word(const char **str, t_fp_charset charset)
{
	size_t	flag;
	size_t	len;

	len = 0;
	flag = !charset((*str)[len]);
	while ((*str)[len] && !charset((*str)[len]) && flag)
		len += 1;
	while ((*str)[len] && charset((*str)[len]) && !flag)
		len += 1;
	*str += len;
	return (len * flag);
}

char	**ft_split(char	const *str, t_fp_charset charset)
{
	char		**out;
	size_t		len;
	size_t		words;
	char const	*tmp;
	size_t		index;

	if (str == NULL)
		return (NULL);
	tmp = str;
	words = -(!tmp);
	index = 0;
	while (tmp && *tmp)
		words += (!!ft_is_word(&tmp, charset));
	out = ft_calloc(words + 1, sizeof(char *));
	while (out && *str && index <= words)
	{
		tmp = str;
		len = ft_is_word(&str, charset);
		if (len)
		{
			out[index] = ft_substr(tmp, 0, len);
			index += 1;
		}
	}
	return (out);
}

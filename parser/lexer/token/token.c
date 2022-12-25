/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:49:10 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/25 18:03:38 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	token_create(t_token_type type, char *substr)
{
	t_token	output;

	if (substr == NULL)
		return (NULL);
	output = ft_calloc(1, sizeof(struct s_token));
	if (output)
		(*output) = (struct s_token){type, substr};
	return (output);
}

void	token_destroy(void *input)
{
	t_token	token;

	token = input;
	if (token == NULL)
		return ;
	free(token->input);
	free(token);
}

t_token	token_match(char **str, t_token_type type, char *start, char *end)
{
	size_t	match_len;
	char	*tmp;
	t_token	token;

	if (!str || !(*str) || !(**str) || !start || !(*start))
		return (NULL);
	match_len = ft_strlen(start);
	if (ft_strncmp(*str, start, match_len) != 0)
		return (NULL);
	if (end && (*end))
	{
		tmp = (*str) + match_len;
		tmp = ft_strnstr(tmp, end, ft_strlen(tmp));
		if (end)
			match_len = (tmp + ft_strlen(end)) - (*str);
	}
	token = token_create(type, ft_substr(*str, 0, match_len));
	(*str) += (match_len * (token != NULL));
	return (token);
}

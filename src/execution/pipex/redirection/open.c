/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:32:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/21 10:54:15 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <unistd.h>

int	redir_in(t_token token)
{
	return (f_open(token->input, O_RDONLY, 0));
}

int	redir_out(t_token token)
{
	if (ft_strncmp(token->input, "/dev/stdout", ft_strlen("/dev/stdout")) == 0)
		return (-3);
	return (f_open(token->input, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	redir_append(t_token token)
{
	return (f_open(token->input, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

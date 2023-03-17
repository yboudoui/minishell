/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:32:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/17 14:32:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	redir_in(t_token token)
{
	return (f_open(token->input, O_RDONLY, 0));
}

int	redir_out(t_token token)
{
	return (f_open(token->input, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	redir_append(t_token token)
{
	return (f_open(token->input, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

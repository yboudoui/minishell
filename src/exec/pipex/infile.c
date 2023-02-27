/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:21:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 18:57:59 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int infile(t_list redir_in)
{
	int	fd;
	t_token token;

	if (redir_in == NULL)
		return (STDIN_FILENO);
	fd = -1;
	while (redir_in)
	{
		token = redir_in->content;
		fd = f_open(token->input, O_RDONLY, 0);
		printf("fd = %d\n", fd);
		if (fd == -1 && redir_in->next == NULL)
			return (-1);
		if (fd == -1 && redir_in->next != NULL)
			return (-1);
		if (fd != -1 && redir_in->next != NULL)
			close_fd(&fd);
		if (fd != -1 && redir_in->next == NULL)
			return (fd);
		redir_in = redir_in->next;
	}
	return (STDIN_FILENO);
}

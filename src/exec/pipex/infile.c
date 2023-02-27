/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:21:19 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/27 17:37:22 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <unistd.h>

int infile(t_list redir_in)
{
	int	fd;
	t_token token;

	if (redir_in == NULL)
	{
		printf("redir_in is NULL\n");
		return (STDIN_FILENO);
	}
	printf("HERE\n");
	token = (t_token)redir_in->content;
	printf("redir_in = %s\n", token->input);
	printf("redir_in = %p\n", token->input);
	if (redir_in->content == NULL)
		printf("it works\n");
	exit(1);
	if (redir_in == NULL)
		return (STDIN_FILENO);
	fd = -1;
	while (redir_in)
	{
		fd = f_open((char *)redir_in->content, O_RDONLY, 0);
		if (fd == -1 && redir_in->next == NULL)
			return (-1);
		if (fd != -1 && redir_in->next != NULL)
			close_fd(&fd);
		if (fd != -1 && redir_in->next == NULL)
			return (fd);
		redir_in = redir_in->next;
	}
	return (STDIN_FILENO);
}

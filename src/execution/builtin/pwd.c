/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:42:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:27:38 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(char *argv[])
{
	char	*buffer;
	size_t	size;

//	if (argv == NULL || *argv != "pwd")
//		return (EXIT_FAILURE);
	argv += 1;
	size = 512;
	buffer = NULL;
	while (buffer == NULL)
	{
		free(buffer);
		buffer = ft_calloc(size,sizeof(char));
		if (buffer == NULL)
			return (EXIT_FAILURE);
		if (getcwd(buffer, size))
			break ;
		size *= 2;
		buffer = NULL;
	}
	write(STDIN_FILENO, buffer, ft_strlen(buffer));
	write(STDIN_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

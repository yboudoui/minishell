/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:55:39 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/25 16:56:56 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	generic_err(t_pipex *pipex, char *str, int system, int exitcode)
{
	char	*s;

	if (system == 1)
		perror(str);
	/* else if (system == 2) */
	/* { */
	/* 	s = ft_strjoin(str, ": command not found\n"); */
	/* 	ft_putstr_fd(s, STDERR_FILENO); */
	/* 	free(s); */
	/* } */
	/* else if (system == 3) */
	/* { */
	/* 	s = ft_strjoin(str, ": No such file or directory\n"); */
	/* 	ft_putstr_fd(s, STDERR_FILENO); */
	/* 	free(s); */
	/* } */
	/* else if (str != NULL) */
	/* 	write(2, str, ft_strlen(str)); */
	/* free_pipex(pipex); */
	/* close_pipex(pipex); */
	/* exit(exitcode); */
}

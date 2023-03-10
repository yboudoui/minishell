/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:31:39 by kdhrif            #+#    #+#             */
/*   Updated: 2023/03/10 18:35:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_dir(char *path)
{
	struct stat	path_stat;

	path_stat = (struct stat){0};
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

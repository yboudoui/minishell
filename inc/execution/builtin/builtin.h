/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:39:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include "environment.h"
# include "string.h"

int	builtin_echo(char *argv[]);
int	builtin_pwd(char *argv[]);
int	builtin_cd(char *argv[]);
int	builtin_export(char *argv[], t_env_list env);

#endif

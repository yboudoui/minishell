/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:39:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 11:44:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include "environment.h"
# include "string.h"

typedef int	(*t_fp_builtin)(char *[]);

int				builtin_cd(char *argv[]);
int				builtin_pwd(char *argv[]);
int				builtin_env(char *argv[]);
int				builtin_exit(char *argv[]);
int				builtin_echo(char *argv[]);
int				builtin_unset(char *argv[]);
int				builtin_export(char *argv[]);

t_fp_builtin	is_builtin(char *argv);
#endif

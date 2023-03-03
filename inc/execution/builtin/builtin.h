/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:39:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 19:31:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include "environment.h"
# include "string.h"

typedef int	(*t_fp_builtin)(char *[], t_env_list *);

int	builtin_cd(char *argv[], t_env_list *env);
int	builtin_pwd(char *argv[], t_env_list *env);
int	builtin_env(char *argv[], t_env_list *env);
int	builtin_exit(char *argv[], t_env_list *env);
int	builtin_echo(char *argv[], t_env_list *env);
int	builtin_unset(char *argv[], t_env_list *env);
int	builtin_export(char *argv[], t_env_list *env);

t_fp_builtin	is_builtin(char *argv);
#endif

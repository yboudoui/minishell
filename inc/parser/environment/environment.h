/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:05:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:20:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "utils.h"

typedef struct s_env_var	*t_env_var;

struct s_env_var {
	char	*name;
	char	*value;
};

typedef struct s_env_list	*t_env_list;

struct s_env_list {
	t_env_var	var;
	t_env_list	next;
	t_env_list	prev;
};

t_env_var	environment_variable_create(char *name, char *value);
void		environment_variable_destroy(void *input);
t_env_var	env_var_create(char *str);
void		environment_variable_replace(t_env_var *dest, t_env_var src);

t_env_list	environment_list_create(char *envp[]);
void		environment_list_destroy(void *data);

#endif

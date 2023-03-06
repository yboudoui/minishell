/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:05:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/06 18:54:19 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "string.h"
# include "list.h"

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

t_env_list	env_list_singleton(t_env_list list);

bool		env_list_create(char *envp[]);
void		env_list_destroy(void);
void		env_list_insert(t_env_var var);
void		env_list_insert_new(char *name, char *value);
t_env_var	env_find(char *name);
char		*env_get_value(char *name);

t_env_var	env_variable_create(char *name, char *value);
void		env_variable_destroy(void *input);
t_env_var	env_var_create(char *str);
void		env_variable_replace(t_env_var *dest, t_env_var src);

#endif

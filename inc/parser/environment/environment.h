/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:05:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/19 12:35:13 by yboudoui         ###   ########.fr       */
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
bool		env_list_insert_new(char *name, char *value);
char		**env_list_get_value_list(char *name);
t_env_var	env_find(char *name, size_t start, size_t end);
void		env_remove(char *name, size_t start, size_t end);
char		*env_get_value(char *name, size_t start, size_t end);

t_env_var	env_variable_create(char *name, char *value);
void		env_variable_destroy(void *input);
t_env_var	env_var_create(char *str);
void		env_variable_replace(t_env_var *dest, t_env_var src);

char		*env_find_and_expand_var(char *in);
bool		env_find_and_expand_var_to(char **str);

int			bash_definition_name(char *str);
int			bash_definition_variable(char *str);

#endif

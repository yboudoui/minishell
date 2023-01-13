/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:05:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/13 08:15:20 by yboudoui         ###   ########.fr       */
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

t_env_var	env_var_create(char *str);
void		env_var_destroy(void *input);
t_list		env_var_as_path(t_env_var var);

t_list		environment_list_create(char *envp[]);
void		environment_list_destroy(void *data);

#endif

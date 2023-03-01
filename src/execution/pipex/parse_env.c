/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:07:49 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/28 15:10:18 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../inc/minishell.h"

char **parse_env(t_list env)
{
	char	**envp;
	int		i;
	t_env_var tmp;
	char *tmp1;
	char *tmp2;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	null_str_err((char *)envp);
	while (env)
	{
		tmp = (t_env_var)env->content;
		tmp1 = ft_strjoin(tmp->name, "=");
		null_str_err(tmp1);
		tmp2 = ft_strjoin(tmp1, tmp->value);
		null_str_err(tmp2);
		free(tmp1);
		envp[i] = tmp2;
		null_str_err(envp[i]);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:59:20 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/15 16:33:20 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../../inc/minishell.h"

static inline int	my_name_is_norminette(bool *error)
{
	*error = true;
	return (2);
}

static inline int check_overflow_error(long long int n, char *str, bool *error)
{
	char *cmp;

	if (n == LONG_MIN && ft_strncmp(str, "-9223372036854775808", 20) == 0)
		return (0);
	else
	{
		cmp = ft_itoa(n);
		if (ft_strncmp(str, cmp, ft_strlen(str)) != 0)
		{
			free(cmp);
			return (my_name_is_norminette(error));
		}
		free(cmp);
	}
	return (0);
}

static inline long long int	ft_atoi_exit(char *str, bool *error)
{
	long long int	n;
	long long int	neg;
	int				i;

	neg = 0;
	i = 0;
	n = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg = -1;
	if (str[i] == '+' || str[i] == '-')
		return (my_name_is_norminette(error));
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		n = n * 10 + str[i++] - '0';
	if (str[i])
		return (my_name_is_norminette(error));
	if (neg)
		n *= -1;
	if (check_overflow_error(n, str, error))
		return (2);
	return (n);
}


int	more_norminette(char **argv, bool *error, int exit_code)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	printf("exit\n");
	if (*error == true && exit_code == 2)
	{
		generic_err(argv[0], "numeric argument required\n", 2);
		meta_exit(exit_code, NULL);
	}
	if (i > 1)
	{
		generic_err("exit", "too many arguments\n", 2);
		g_global.exit_code = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(char *argv[])
{
	long long int	exit_code;
	bool			error;
	int				i;

	error = false;
	i = 0;
	exit_code = 0;
	argv += 1;
	if (*argv != NULL)
	{
		exit_code = ft_atoi_exit(argv[0], &error);
		if (exit_code > 0)
			exit_code %= 256;
		else
		{
			exit_code *= -1;
			exit_code %= 256;
			exit_code = 256 - exit_code;
		}
	}
	if (more_norminette(argv, &error, exit_code) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	meta_exit(exit_code, NULL);
	return (EXIT_SUCCESS);
}

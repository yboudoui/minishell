/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:05:07 by yboudoui          #+#    #+#             */
/*   Updated: 2023/03/21 14:05:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include "list.h"
# include "memory.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>

typedef bool	(*t_fp_charset)(int);
t_fp_charset	str_charset(char *str);

bool			is_space(int c);
bool			is_alnum(char c);
bool			is_alpha(char c);
bool			is_digit(char c);
bool			is_empty(char *str);

int				ft_atoi(const char *nptr);
char			*ft_strchr(const char *s, int c);

char			*ft_itoa(long long int n);

char			*ft_strtrim(char const *s1, char const *set);
void			str_new_empty(char **str);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strrchr(const char *s, int c);

char			*ft_strjoin(char const *s1, char const *s2);
char			*str_join_list(char *str[], char *delimiter);

char			*str_merge_list(char *str[]);
char			*str_merge_new_line(char *s1, char *s2);
void			str_merge_to(char **str, char *s);
void			str_merge_list_to(char **str, char *list[]);

int				string_cmp(const char *s1, const char *s2);

int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_str_find_prefix(char *big, char *little);
bool			string_end_with(const char *str, const char *suffix);

char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);

char			*str_slice_section(char *str, char *start, char *end);
char			*str_slice_prefix(char *str, char *prefix);
int				str_must_slice_section(char *str, char **section, char **out);
char			*str_slice_charset(char *str, t_fp_charset charset);

void			string_array_destroy(void *data);

char			**ft_split(char	const *str, t_fp_charset charset);

size_t			ft_putchar_fd(char c, int fd);
size_t			ft_putstr_fd(char *s, int fd);
size_t			ft_putnl_fd(char *s, int fd);

#endif

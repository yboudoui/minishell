/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:27:41 by kdhrif            #+#    #+#             */
/*   Updated: 2023/02/22 14:57:49 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

/**************** LIST ****************/
typedef struct s_list	*t_list;
typedef void			(*t_fp_destroy_content)(void*);

struct s_list {
	void	*content;
	t_list	next;
	t_list	prev;
};
// src/utils/list/list.c
t_list	list_create(void *content);
bool	list_create_back(t_list *root, void *content);

// src/utils/list/list_destroy.c
void	list_destroy(t_list lst, t_fp_destroy_content del);
void	list_clear(t_list *lst, t_fp_destroy_content del);

// src/utils/list/list_add.c
bool	list_add_back(t_list *root, t_list new);
bool	list_add_front(t_list *lst, t_list new);

// src/utils/list/list_utils.c
int		ft_lstsize(t_list lst);
t_list	ft_lstmap(t_list lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list lst, void (*f)(void *));

// src/utils/list/list_remove.c
void	list_remove_one(t_list *root, t_fp_destroy_content del);

// src/utils/list/list_last.c
t_list	list_last(t_list lst);
size_t	list_size(t_list lst);

// src/utils/list/list_str_array_to_list.c
t_list	str_array_to_list(char *str_array[]);

/***************** LEXER *****************/
char	*lexer(char *input, t_list *out);

/***************** SYNTAXER *****************/
// src/parser/syntaxer.c 
bool	syntaxer(t_list *root);

/***************** PARSER *****************/
typedef enum e_token_kind {
	TOKEN_VALUE		= (1UL << 8),
	TOKEN_OPERATOR	= (1UL << 9),
}	t_token_kind;

typedef enum e_token_type {
	TOKEN_SPACES				=	0	| TOKEN_VALUE,
	TOKEN_WORD					=	1	| TOKEN_VALUE,
	TOKEN_DOUBLE_QUOTES			=	2	| TOKEN_VALUE,
	TOKEN_SIMPLE_QUOTES			=	3	| TOKEN_VALUE,
	TOKEN_WILDCARD				=	4	| TOKEN_VALUE,
	TOKEN_COMMANDE				=	5	| TOKEN_VALUE,
	TOKEN_REDIRECT_IN			=	6	| TOKEN_OPERATOR,
	TOKEN_HERE_DOCUMENT			=	7	| TOKEN_OPERATOR,
	TOKEN_PIPE					=	8	| TOKEN_OPERATOR,
	TOKEN_REDIRECT_OUT			=	9	| TOKEN_OPERATOR,
	TOKEN_REDIRECT_OUT_APPEND	=	10	| TOKEN_OPERATOR,
	TOKEN_AND					=	11	| TOKEN_OPERATOR,
	TOKEN_OR					=	12	| TOKEN_OPERATOR,
	TOKEN_SUBSHELL				=	13	| TOKEN_OPERATOR,
	MAX_TOKEN					=	14	| TOKEN_OPERATOR,
}	t_token_type;

typedef struct s_token	*t_token;

struct s_token {
	t_token_type	type;
	char			*input;
};

// src/parser/lexer/token.c
t_token	token_create(t_token_type type, char *substr);
t_token	token_dup(t_token src);
void	token_destroy(void *input);
bool	token_match(char *str, t_list *output);
bool	token_list_sanitizer(t_list *lst);

// src/parser/lexer/matching.c
char	*tokenizer(char *input, t_list *out);

// ?
void	readline_handler(bool (*handler)(char *));

/****************** MEMORY UTILS *****************/

// src/utils/memory/ft_calloc.c
void	*ft_calloc(size_t nmemb, size_t size);

// src/utils/memory/ft_memcpy.c
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*memory_dup(void *src, size_t n);

/****************** STRING UTILS *****************/
typedef bool	(*t_fp_is_charset)(int);
bool	is_space(int c);
bool	is_empty(char *str);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

char	*ft_strjoin(char const *s1, char const *s2);
char	*str_merge(char *str, ...) __attribute__((sentinel));

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_str_find_prefix(char *big, char *little);

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*str_slice_section(char *str, char *start, char *end);
int		str_must_slice_section(char *str, char **section, char **out);
char	*str_slice_prefix(char *str, char *prefix);
char	*str_slice_charset(char *str, t_fp_is_charset charset);

char	**list_to_str_array(t_list lst, bool (*cast_content)(void *, char **));
void	string_array_destroy(void *data);

char	**ft_split(char	const *str, char c);

// ft_putchar_fd.c
size_t	ft_putchar_fd(char c, int fd);

// ft_putstr_fd.c
size_t	ft_putstr_fd(char *s, int fd);

/************** MODULES **************/
t_token	token_is_spaces(char *str);

t_token	token_is_wildcard(char *str);
t_token	token_is_here_document(char *str);

t_token	token_is_redirect_in(char *str);
t_token	token_is_semicolon(char *str);

t_token	token_is_double_quote(char *str);
t_token	token_is_simple_quote(char *str);
t_token	token_is_subshell(char *str);

t_token	token_is_redirect_out_append(char *str);
t_token	token_is_redirect_out(char *str);

t_token	token_is_redirect_err_append(char *str);
t_token	token_is_redirect_err(char *str);

t_token	token_is_and(char *str);
t_token	token_is_background(char *str);

t_token	token_is_or(char *str);
t_token	token_is_pipe(char *str);

/****************** COMMANDS *****************/
typedef struct s_commande	*t_commande;

struct s_commande {
	t_list			argv;
	t_list			redir_in;
	t_list			redir_out;
	t_list			redir_out_append;
	t_list			here_document;
};

t_commande	commande_create(t_list lst);
void		commande_destroy(void *data);


/****************** EXPANDER *****************/
void	commande_expand_variable(t_list env, t_commande cmd);

/****************** ENVIRONMENT *****************/
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


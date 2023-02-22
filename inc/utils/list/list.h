/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:11:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/02/22 16:15:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "memory.h"
# include <stdbool.h>

typedef struct s_list	*t_list;
typedef void			(*t_fp_destroy_content)(void*);

struct s_list {
	void	*content;
	t_list	next;
	t_list	prev;
};

t_list	list_create(void *content);
bool	list_create_back(t_list *root, void *content);

void	list_destroy(t_list lst, t_fp_destroy_content del);
void	list_clear(t_list *lst, t_fp_destroy_content del);

bool	list_add_back(t_list *root, t_list new);
bool	list_add_front(t_list *lst, t_list new);

int		ft_lstsize(t_list lst);
void	*list_to_array(t_list lst, void *(*f)(void *));

t_list	ft_lstmap(t_list lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list lst, void (*f)(void *));

void	list_remove_one(t_list *root, t_fp_destroy_content del);

t_list	list_last(t_list lst);
size_t	list_size(t_list lst);

t_list	str_array_to_list(char *str_array[]);

#endif

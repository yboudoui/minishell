/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:41:13 by yboudoui          #+#    #+#             */
/*   Updated: 2022/12/24 21:23:56 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_destroy(t_list lst, t_fp_destroy_content del)
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

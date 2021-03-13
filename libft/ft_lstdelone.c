/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:11:35 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/25 21:29:18 by Tsak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_lstdelone(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	if ((*lst)->prev)
	{
		tmp = (*lst)->prev;
		tmp->next = (*lst)->next;
	}
	tmp = NULL;
	if ((*lst)->next)
	{
		tmp = (*lst)->next;
		tmp->prev = (*lst)->prev;
	}
	if (del)
		(*del)((*lst)->content);
	if (!(tmp && tmp->prev == ft_lstfirst(tmp)))
		tmp = NULL;
	free(*lst);
	*lst = tmp;
	*lst = NULL;
}

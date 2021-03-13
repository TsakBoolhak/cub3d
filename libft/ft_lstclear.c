/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:09:55 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/20 00:03:08 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	*lst = ft_lstfirst(*lst);
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(lst, del);
		*lst = tmp;
	}
}

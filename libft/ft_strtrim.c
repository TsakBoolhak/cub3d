/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:07:35 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/08 23:40:31 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"
#include "ft_memory.h"

char	*ft_strtrim(char const *src, char const *set)
{
	char	*dst;
	size_t	len;

	if (!src)
		return (NULL);
	else if (!set)
		return (ft_strdup(src));
	while (*src && ft_strchr(set, *src))
		src++;
	if (!*src)
		return (ft_strdup(""));
	len = ft_strlen(src);
	while (src + len >= src && ft_strchr(set, *(src + len - 1)))
		len--;
	dst = ft_strndup(src, len);
	return (dst);
}

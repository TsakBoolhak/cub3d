/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:43:51 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 20:43:54 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	return_error(char *str, int ret)
{
	ft_putstr_fd(str, 2);
	return (ret);
}

char	**ft_add_str_to_tab(char **tab, char *line)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	new_tab[i + 1] = NULL;
	new_tab[i] = line;
	if (!new_tab[i])
		return (ft_free_tab((void **)new_tab));
	while (i-- > 0)
		new_tab[i] = tab[i];
	free(tab);
	return (new_tab);
}

size_t	ft_count_char_in_str(const char *s, int c)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strchr(s, c);
	while (tmp)
	{
		i++;
		if (!c)
			return (i);
		tmp = ft_strchr(tmp + 1, c);
	}
	return (i);
}

int	ft_strischarset(char *str, char *charset)
{
	size_t	i;

	if (!str || !charset)
		return (0);
	i = 0;
	if (!*str)
		return (1);
	else if (!*charset || !*str)
		return (0);
	while (str[i] && ft_strchr(charset, str[i]))
		i++;
	return (str[i] == '\0' && i > 0);
}

int	ft_strisdigit(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (str[i] == '\0' && i > 0);
}

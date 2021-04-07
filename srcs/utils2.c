/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 21:55:28 by acabiac           #+#    #+#             */
/*   Updated: 2021/03/02 21:55:34 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

int	rgb_to_r(int rgb)
{
	int	r;

	r = rgb << 8;
	return (r >> 24);
}

int	rgb_to_g(int rgb)
{
	int	g;

	g = rgb << 16;
	return (g >> 24);
}

int	rgb_to_b(int rgb)
{
	int	b;

	b = rgb << 24;
	return (b >> 24);
}

int	argb_to_int(int a, int r, int g, int b)
{
	return ((a << 24) + (r << 16) + (g << 8) + b);
}

int	check_overflow(char *nb)
{
	char	*max_int;
	int		max_len;
	int		nb_len;
	int	 	ret;
	int		tab[2];

	max_int = ft_longtoa_base(INT_MAX, "0123456789");
	if (!max_int || !nb)
		return (-1);
	ret = 0;
	max_len = ft_strlen(max_int);
	nb_len = ft_strlen(nb);
	if (nb_len > max_len)
		ret = -1;
	tab[0] = ft_atoi_n(max_int, max_len - 1);
	tab[1] = ft_atoi_n(nb, nb_len - 1);
	if (nb_len == max_len)
	{
		if (tab[0] < tab[1]
			|| (tab[0] == tab[1] && nb[nb_len - 1] > max_int[max_len - 1]))
			ret = -1;
	}
	free(max_int);
	return (ret);
}

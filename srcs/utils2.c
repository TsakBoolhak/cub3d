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

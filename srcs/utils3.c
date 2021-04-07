/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:04:22 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:04:24 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	degree_to_radiant(double degree)
{
	return (degree * M_PI / 180.0);
}

int	get_x_vector(double dir)
{
	if (dir == 0.0 || dir == 180.0)
		return (0);
	else if (dir < 180.0)
		return (1);
	else
		return (-1);
}

int	get_y_vector(double dir)
{
	if (dir == 270.0 || dir == 90.0)
		return (0);
	else if (dir < 90.0 || dir > 270.0)
		return (-1);
	else
		return (1);
}

double	get_rad_for_x_cross(double dir)
{
	double	rad;

	if (dir <= 90.0)
		rad = 90.0 - dir;
	else if (dir <= 180.0)
		rad = dir - 90.0;
	else if (dir <= 270.0)
		rad = 270.0 - dir;
	else
		rad = dir - 270.0;
	rad = degree_to_radiant(rad);
	return (rad);
}

double	get_rad_for_y_cross(double dir)
{
	double	rad;

	if (dir <= 90.0)
		rad = dir;
	else if (dir <= 180.0)
		rad = 180.0 - dir;
	else if (dir <= 270.0)
		rad = dir - 180.0;
	else
		rad = 360.0 - dir;
	rad = degree_to_radiant(rad);
	return (rad);
}

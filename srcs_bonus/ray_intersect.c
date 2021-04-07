/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:07:34 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:07:35 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h" 

t_pos	get_next_intersect(t_pos origin, double rad, t_coord vect, int loop)
{
	t_pos	cross;
	double	hypo;

	cross.x = origin.x;
	cross.y = origin.y;
	hypo = 1.0 / cos(rad);
	if (!loop)
	{
		cross.x = (origin.x + (hypo * cos(rad) * vect.x));
		cross.y = (origin.y + (hypo * sin(rad) * vect.y));
	}
	else
	{
		cross.y = (origin.y + (hypo * cos(rad) * vect.y));
		cross.x = (origin.x + (hypo * sin(rad) * vect.x));
	}
	return (cross);
}

t_pos	get_first_x_intersect(t_pos origin, double rad, t_coord vect)
{
	t_pos	x_cross;
	double	hypo;

	x_cross.x = origin.x;
	x_cross.y = origin.y;
	if (vect.x > 0)
		hypo = (ceil(origin.x) - origin.x) / cos(rad);
	else
		hypo = (origin.x - floor(origin.x)) / cos(rad);
	x_cross.x = (origin.x + (hypo * cos(rad) * vect.x));
	x_cross.y = (origin.y + (hypo * sin(rad) * vect.y));
	return (x_cross);
}

t_pos	get_first_y_intersect(t_pos origin, double rad, t_coord vect)
{
	t_pos	y_cross;
	double	hypo;

	y_cross.x = origin.x;
	y_cross.y = origin.y;
	if (vect.y > 0)
		hypo = (ceil(origin.y) - origin.y) / cos(rad);
	else
		hypo = (origin.y - floor(origin.y)) / cos(rad);
	y_cross.y = (origin.y + (hypo * cos(rad) * vect.y));
	y_cross.x = (origin.x + (hypo * sin(rad) * vect.x));
	return (y_cross);
}

void	check_for_sprite(t_pos *pos, t_coord tmp, t_cub *cub, int loop)
{
	char	**map;

	map = cub->map;
	if (!loop && pos->x > cub->player.x && tmp.x > 0
		&& map[tmp.y][tmp.x - 1] == '2')
		tmp.x--;
	else if (loop && pos->y > cub->player.y && tmp.y > 0
		&& map[tmp.y - 1][tmp.x] == '2')
		tmp.y--;
	else if (map[tmp.y][tmp.x] == '2')
		tmp.x = tmp.x;
	else if (!loop && pos->x < cub->player.x
		&& tmp.x < cub->map_w - 1 && map[tmp.y][tmp.x + 1] == '2')
		tmp.x++;
	else if (loop && pos->y < cub->player.y && tmp.y < cub->map_h - 1
		&& map[tmp.y + 1][tmp.x] == '2')
		tmp.y++;
	set_sprite_dist(tmp, pos, cub);
}

void	intersect_loop(t_pos *pos, t_cub *cub, int loop)
{
	t_coord	tmp;
	char	**map;

	tmp.x = (int)pos->x;
	tmp.y = (int)pos->y;
	map = cub->map;
	while (tmp.x < cub->map_w && tmp.x >= 0 && tmp.y < cub->map_h && tmp.y >= 0)
	{
		check_for_sprite(pos, tmp, cub, loop);
		if (map[tmp.y][tmp.x] == '1' || map[tmp.y][tmp.x] == ' ')
			break ;
		if (tmp.x > 0 && map[tmp.y - (loop == 1)][tmp.x - (!loop)] == '1')
			break ;
		if (tmp.x > 0 && map[tmp.y - (loop == 1)][tmp.x - (!loop)] == ' ')
			break ;
		*pos = get_next_intersect(*pos, cub->ray.rad, cub->ray.vect, loop);
		tmp.x = (int)pos->x;
		tmp.y = (int)pos->y;
	}
	if (!loop && pos->x > cub->player.x)
		pos->x = floor(pos->x);
	else if (loop && pos->y > cub->player.y)
		pos->y = floor(pos->y);
}

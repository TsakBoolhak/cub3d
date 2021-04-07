/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:07:47 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:07:48 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

double	get_distance(t_pos pos1, t_pos pos2)
{
	double	dist;

	dist = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
	return (dist);
}

int	get_sprite_height(t_cub *cub, t_sprite *sprite)
{
	double	line_height;
	int		start;
	int		end;

	line_height = cub->height / sprite->mid.dir;
	line_height *= cub->ray.fish;
	line_height = round(line_height);
	start = -line_height / 2 + cub->height / 2;
	end = line_height / 2 + cub->height / 2;
	sprite->true_sprite_h = end - start;
	if (start < 0)
		start = 0;
	if (end >= cub->height)
		end = cub->height - 1;
	return (end - start);
}

int	set_angle(t_pos player, t_sprite *sprite, t_pos *hit, t_pos *angle)
{
	if (sprite->rad < 0)
		sprite->rad *= -1;
	angle->x = atan2(player.y - sprite->mid.y, player.x - sprite->mid.x);
	angle->x -= atan2(player.y - sprite->start.y, player.x - sprite->start.x);
	angle->y = atan2(player.y - sprite->mid.y, player.x - sprite->mid.x);
	angle->y -= atan2(player.y - hit->y, player.x - hit->x);
	if (angle->x < 0)
		angle->x *= -1;
	if (angle->y < 0)
		angle->y *= -1;
	if (angle->x > 5.0)
		angle->x = 6.28 - angle->x;
	if (angle->y > 5.0)
		angle->y = 6.28 - angle->y;
	if (angle->y > angle->x)
		return (-1);
	angle->x = get_distance(player, sprite->mid);
	angle->x /= cos(angle->y);
	angle->y = atan2(player.y - hit->y, player.x - hit->x);
	return (0);
}

int	set_sprite(t_cub *cub, t_sprite *sprite, t_pos *hit, t_pos *sprite_hit)
{
	t_pos	angle;

	if (set_angle(cub->player, sprite, hit, &angle) == -1)
		return (-1);
	sprite_hit->x = cub->player.x - (angle.x * cos(angle.y));
	sprite_hit->y = cub->player.y - (angle.x * sin(angle.y));
	if ((int)(sprite_hit->y) != (int)(sprite->mid.y)
		|| (int)(sprite_hit->x) != (int)sprite->mid.x)
		return (-1);
	if (cub->ray.fov_angle > 90.0 && cub->ray.fov_angle < 270.0
		&& cub->player.y > sprite_hit->y)
		return (-1);
	if ((cub->ray.fov_angle < 90.0 || cub->ray.fov_angle > 270.0)
		&& cub->player.y < sprite_hit->y)
		return (-1);
	if (cub->ray.fov_angle < 180.0 && cub->player.x > sprite_hit->x)
		return (-1);
	if (cub->ray.fov_angle > 180.0 && cub->player.x < sprite_hit->x)
		return (-1);
	return (0);
}

void	set_sprite_dist(t_coord	sprite, t_pos *hit, t_cub *cub)
{
	t_sprite	**sprites;
	int			i;
	t_pos		sprite_hit;
	t_sprite	*tmp;

	sprites = cub->sprites;
	i = 0;
	while (sprites && sprites[i])
	{
		if (sprites[i]->coord.x == sprite.x && sprites[i]->coord.y == sprite.y)
		{
			if (set_sprite(cub, sprites[i], hit, &sprite_hit) != -1)
			{
				tmp = sprites[i];
				tmp->mid.dir = get_distance(cub->player, sprite_hit);
				tmp->hit = sprite_hit;
				tmp->hit.dir = get_distance(tmp->start, tmp->hit);
				tmp->sprite_h = get_sprite_height(cub, tmp);
			}
			return ;
		}
		i++;
	}
}

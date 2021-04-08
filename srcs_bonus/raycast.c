/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:07:41 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:07:42 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

t_pos	closest_hit(t_pos orig, t_pos x_pos, t_pos y_pos, t_cub *cub)
{
	t_pos	dist;

	dist.y = sqrt(pow(orig.x - y_pos.x, 2.0) + pow(orig.y - y_pos.y, 2.0));
	dist.x = sqrt(pow(orig.x - x_pos.x, 2.0) + pow(orig.y - x_pos.y, 2.0));
	if (dist.x < dist.y)
	{
		cub->ray.hit_dist = dist.x;
		cub->ray.shadow_ratio = 8 / dist.x;
		if (cub->ray.shadow_ratio > 1.0)
			cub->ray.shadow_ratio = 1.0;
		cub->ray.side = 0;
		return (x_pos);
	}
	else
	{
		cub->ray.hit_dist = dist.y;
		cub->ray.shadow_ratio = 8 / dist.y;
		if (cub->ray.shadow_ratio > 1.0)
			cub->ray.shadow_ratio = 1.0;
		cub->ray.side = 1;
		return (y_pos);
	}
}

t_pos	get_wall_hit(t_pos orig, double fov_angle, t_cub *cub)
{
	t_pos	x_cross;
	t_pos	y_cross;

	cub->ray.vect.x = get_x_vector(fov_angle);
	cub->ray.vect.y = get_y_vector(fov_angle);
	cub->ray.rad = get_rad_for_x_cross(fov_angle);
	x_cross = get_first_x_intersect(orig, cub->ray.rad, cub->ray.vect);
	intersect_loop(&x_cross, cub, 0);
	cub->ray.rad = get_rad_for_y_cross(fov_angle);
	y_cross = get_first_y_intersect(orig, cub->ray.rad, cub->ray.vect);
	intersect_loop(&y_cross, cub, 1);
	return (closest_hit(orig, x_cross, y_cross, cub));
}

double	get_screen_dist(int width)
{
	double	rad;
	double	half_width;

	rad = degree_to_radiant(FOV / 2.0);
	half_width = (double)(width) / 2.0;
	return (half_width / tan(rad));
}

double	get_wall_height(double fisheye_correct, t_cub *cub)
{
	double	wall_dist;
	double	line_height;
	int		start;
	int		end;

	wall_dist = cub->ray.hit_dist;
	line_height = cub->height / wall_dist;
	line_height *= fisheye_correct;
	line_height = round(line_height);
	start = -line_height / 2 + cub->height / 2;
	end = line_height / 2 + cub->height / 2;
	cub->true_wall_h = end - start;
	if (start < 0)
		start = 0;
	if (end >= cub->height)
		end = cub->height - 1;
	return ((end - start));
}

void	raycast_loop(t_cub *cub)
{
	int		i;
	t_ray	*ray;

	i = 0;
	ray = &cub->ray;
	init_sprites(cub->sprites, cub);
	while (i < cub->width)
	{
		init_sprites_dist(cub->sprites, cub);
		ray->hit = get_wall_hit(cub->player, ray->fov_angle, cub);
		sort_sprite_tab(cub->sprites);
		draw_ray_to_minimap(cub);
		ray->fish = ray->fov_angle - cub->player.dir;
		if (ray->fish < 0.0)
			ray->fish *= -1.0;
		ray->fish = degree_to_radiant(ray->fish);
		ray->fish = (ray->screen_dist / cos(ray->fish)) / ray->screen_dist;
		ray->wall_h = get_wall_height(ray->fish, cub);
		ray->wall_h = round(ray->wall_h);
		draw_wall_to_screen(i, cub);
		ray->fov_angle += ray->angle_increm;
		if (ray->fov_angle >= 360.0)
			ray->fov_angle -= 360.0;
		i++;
	}
}

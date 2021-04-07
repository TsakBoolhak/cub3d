/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:05:04 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:06:16 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void	init_draw_line(t_coord *d, t_coord *s, t_coord start, t_coord end)
{
	d->x = ft_abs(start.x - end.x);
	d->y = ft_abs(start.y - end.y) * -1;
	s->x = -1;
	s->y = -1;
	if (start.x < end.x)
		s->x = 1;
	if (start.y < end.y)
		s->y = 1;
}

void	draw_line(t_coord start, t_coord end, t_data *data, int color)
{
	t_coord	d;
	t_coord	s;
	t_coord	err;

	init_draw_line(&d, &s, start, end);
	err.x = d.x + d.y;
	while (1)
	{
		my_pixel_put(data, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		err.y = 2 * err.x;
		if (err.y >= d.y)
		{
			err.x += d.y;
			start.x += s.x;
		}
		if (err.y <= d.x)
		{
			err.x += d.x;
			start.y += s.y;
		}
	}
}

void	draw_ray_to_minimap(t_cub *cub)
{
	t_coord	start;
	t_coord	end;
	t_pos	hit;
	int		fov_color;

	if (!cub->minmap.minimap.img)
		return ;
	fov_color = argb_to_int(0, 167, 184, 30);
	hit = cub->ray.hit;
	start.y = (int)(round(cub->player.y * (double)(cub->minmap.cell_px_h)));
	start.x = (int)(round(cub->player.x * (double)(cub->minmap.cell_px_w)));
	end.y = (int)(round(hit.y * (double)(cub->minmap.cell_px_h)));
	end.x = (int)(round(hit.x * (double)(cub->minmap.cell_px_w)));
	draw_line(start, end, &cub->minmap.minimap, fov_color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:02:00 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:02:02 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceil_or_floor(int x, int *y, t_cub *cub, int floor)
{
	int	wall_h;

	wall_h = (int)(cub->ray.wall_h);
	if (floor)
	{
		while (*y < cub->height)
		{
			my_pixel_put(&cub->screen, x, *y, cub->floor_rgb);
			(*y)++;
		}
	}
	else
	{
		while (*y < (cub->height - wall_h) / 2)
		{
			my_pixel_put(&cub->screen, x, *y, cub->ceil_rgb);
			(*y)++;
		}
	}
}

void	draw_wall(int x, int *y, int wall_h, t_cub *cub)
{
	int		color;
	char	*dst;
	char	*src;
	t_data	*screen;

	screen = &cub->screen;
	while (*y < cub->height && *y < wall_h + ((cub->height - wall_h) / 2))
	{
		src = get_texture_pixel(y, cub);
		color = *(int *)src;
		dst = screen->addr + (*y * screen->len + x * (screen->bpp / 8));
		*(int *)dst = color;
		(*y)++;
	}
}

void	draw_sprites(int x, t_cub *cub)
{
	int			color;
	int			y;
	int			i;
	int			start;
	t_sprite	**sprites;

	sprites = cub->sprites;
	i = -1;
	while (sprites && sprites[++i] && sprites[i]->mid.dir < cub->ray.hit_dist)
	{
		if (sprites[i]->mid.dir > 0)
		{
			y = ((cub->height - sprites[i]->sprite_h) / 2) - 1;
			start = y + 1;
			while (++y < cub->height && y < sprites[i]->sprite_h + start)
			{
				color = get_sprite_pixel(&y, sprites[i], cub);
				if (color && !cub->draw_buf[y])
				{
					my_pixel_put(&cub->screen, x, y, color);
					cub->draw_buf[y] = 1;
				}
			}
		}
	}
}

void	draw_wall_to_screen(int x, t_cub *cub)
{
	int	y;
	int	wall_h;

	wall_h = (int)(cub->ray.wall_h);
	y = 0;
	draw_ceil_or_floor(x, &y, cub, 0);
	draw_wall(x, &y, wall_h, cub);
	draw_ceil_or_floor(x, &y, cub, 1);
	draw_sprites(x, cub);
}

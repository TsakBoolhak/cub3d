/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:06:37 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:06:38 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

int	get_sprite_pixel(int *y, t_sprite *sprite, t_cub *cub)
{
	t_pos		ratio;
	static int	rety = -2;
	static int	retx = -2;
	t_data		src;
	static int	color = 0;

	ratio.x = sprite->hit.dir;
	ratio.y = (double)(*y - ((cub->height - sprite->true_sprite_h) / 2));
	ratio.y /= (double)(sprite->true_sprite_h);
	src = cub->sprite;
	ratio.x *= (cub->sprite.len / (cub->sprite.bpp / 8));
	ratio.y *= (cub->sprite.height);
	if ((int)(round(ratio.y)) == rety && (int)(round(ratio.y) == retx))
		return (color);
	rety = (int)round(ratio.y);
	retx = (int)round(ratio.x);
	src.addr = src.addr + (rety * src.len + retx * (src.bpp / 8));
	color = *(int *)src.addr;
	return (color);
}

t_data	get_texture_data(t_cub *cub, t_pos *ratio)
{
	t_data	src;

	if (cub->ray.side && cub->ray.hit.y < cub->player.y)
		src = cub->north;
	else if (cub->ray.side)
	{
		src = cub->south;
		ratio->x = 1.0 - ratio->x;
	}
	else if (cub->ray.hit.x < cub->player.x)
	{
		src = cub->west;
		ratio->x = 1.0 - ratio->x;
	}
	else
		src = cub->east;
	ratio->x *= (src.len / (src.bpp / 8));
	ratio->y *= (src.height);
	return (src);
}

char	*get_texture_pixel(int *y, t_cub *cub)
{
	t_pos	ratio;
	t_coord	ret;
	t_data	src;

	if (cub->ray.side)
		ratio.x = cub->ray.hit.x - floor(cub->ray.hit.x);
	else
		ratio.x = cub->ray.hit.y - floor(cub->ray.hit.y);
	ratio.y = (double)(*y - ((cub->height - cub->true_wall_h) / 2));
	ratio.y /= (double)cub->true_wall_h;
	src = get_texture_data(cub, &ratio);
	ret.y = (int)(ratio.y);
	ret.x = (int)(ratio.x);
	src.addr = src.addr + (ret.y * src.len + ret.x * (src.bpp / 8));
	return ((char *)(src.addr));
}

int	get_gun_pixel(int x, int y, int	gheight, t_cub *cub)
{
	t_pos	ratio;
	t_coord	ret;
	t_data	src;
	t_coord	gun;
	int		gwidth;

	gwidth = cub->width / 3;
	gun.x = cub->width / 2 - (gwidth / 2);
	gun.y = gun.x + gwidth;
	ratio.x = (double)(x - gun.x) / (double)(gun.y - gun.x);
	ratio.y = (double)(y - (cub->height - gheight)) / (double)gheight;
	src = cub->gun;
	ratio.x *= (src.len / (src.bpp / 8));
	ratio.y *= src.height;
	ret.y = (int)(ratio.y);
	ret.x = (int)(ratio.x);
	src.addr = src.addr + (ret.y * src.len + ret.x * (src.bpp / 8));
	return (*(int *)src.addr);
}

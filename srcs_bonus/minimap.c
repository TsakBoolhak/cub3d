/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:06:54 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:06:56 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <mlx.h>
#include <math.h>

int	set_mini_map_color(int column, int line, char **map)
{
	char	c;

	c = map[line][column];
	if (c == '1' || c == ' ')
		return (argb_to_int(0, 129, 136, 151));
	else
		return (argb_to_int(0, 10, 55, 134));
}

void	fill_mini_map_line(t_cub *cub, int line)
{
	int			i[2];
	int			column;
	char		*dst;
	int			index;
	t_minimap	map;

	map = cub->minmap;
	*i = 0;
	while (i[0] < map.cell_px_h)
	{
		i[1] = 0;
		column = 0;
		while (column < cub->map_w)
		{
			while (i[1] - (column * map.cell_px_w) < map.cell_px_w)
			{
				index = (line * map.cell_px_w + *i) * map.minimap.len;
				dst = map.minimap.addr + (index + i[1] * map.minimap.bpp / 8);
				*(int *)dst = set_mini_map_color(column, line, cub->map);
				i[1]++;
			}
			column++;
		}
		i[0]++;
	}
}

int	set_minimap_dimensions(t_cub *cub)
{
	cub->minmap.map_px_w = cub->width / 4 ;
	cub->minmap.map_px_h = cub->height / 4 ;
	if (cub->minmap.map_px_w < cub->map_w && cub->width >= cub->map_w * 2)
		cub->minmap.map_px_w = cub->map_w;
	if (cub->minmap.map_px_h < cub->map_h && cub->height >= cub->map_h * 2)
		cub->minmap.map_px_h = cub->map_h;
	if (cub->minmap.map_px_h < cub->map_h || cub->minmap.map_px_w < cub->map_w)
		return (-1);
	cub->minmap.cell_px_w = cub->minmap.map_px_w / cub->map_w;
	cub->minmap.cell_px_h = cub->minmap.map_px_h / cub->map_h;
	if (cub->minmap.cell_px_w < cub->minmap.cell_px_h)
		cub->minmap.cell_px_h = cub->minmap.cell_px_w;
	else
		cub->minmap.cell_px_w = cub->minmap.cell_px_h;
	cub->minmap.map_px_w = cub->map_w * cub->minmap.cell_px_w;
	cub->minmap.map_px_h = cub->map_h * cub->minmap.cell_px_h;
	return (0);
}

int	mini_map_to_img(t_cub *cub)
{
	int			i;
	t_data		tmp;
	t_minimap	map;

	if (set_minimap_dimensions(cub) < 0)
		return (-1);
	map = cub->minmap;
	tmp.img = NULL;
	tmp.img = mlx_new_image(cub->mlx, map.map_px_w, map.map_px_h);
	if (!tmp.img)
		return (-1);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.len, &tmp.end);
	tmp.height = cub->minmap.map_px_h;
	cub->minmap.minimap = tmp;
	i = 0;
	while (i < cub->map_h)
	{
		fill_mini_map_line(cub, i);
		i++;
	}
	return (0);
}

void	draw_pos_to_map(t_minimap *map, t_cub *cub, t_pos pos, int clr)
{
	char	*dst;
	int		i;
	int		j;
	int		line;
	int		column;

	map->cell_px_w = map->minimap.len / (map->minimap.bpp / 8) / cub->map_w;
	map->cell_px_h = map->minimap.height / cub->map_h;
	i = (pos.y - (int)(pos.y)) * (int)(round((double)(map->cell_px_h)));
	j = (pos.x - (int)(pos.x)) * (int)(round((double)(map->cell_px_w)));
	line = (int)pos.y * map->cell_px_h + i;
	line *= map->minimap.len;
	column = (int)pos.x * map->cell_px_w + j;
	column *= (map->minimap.bpp / 8);
	dst = map->minimap.addr + (line + column);
	*(int *)dst = clr;
}

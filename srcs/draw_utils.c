#include "cub3d.h"
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

void	print_sprite_tab(t_sprite **sprites)
{
	int	i;

	i = 0;
	while (sprites && sprites[i])
	{
		printf("sprites[%d] : ", i);
		printf("coord x%d y%d ", sprites[i]->coord.x, sprites[i]->coord.y);
		printf("sprite mid x%g y%g ", sprites[i]->mid.x, sprites[i]->mid.y);
		printf("sprite start x%g y%g ", sprites[i]->start.x, sprites[i]->start.y);
		printf("sprite end x%g y%g ", sprites[i]->end.x, sprites[i]->end.y);
		printf("dist%g, side %d ", sprites[i]->mid.dir, sprites[i]->side);
		printf("rad %g\n", sprites[i]->rad);
		i++;
	}
}

void	draw_sprite_to_minimap(t_cub *cub, t_sprite *sprite)
{
	t_coord	start;
	t_coord	end;
	t_coord	player;
	int		fov_color;

	if (!cub->minmap.minimap.img)
		return ;
	fov_color = argb_to_int(0, 0, 255, 0);
	start.y = (int)(round(sprite->start.y * (double)(cub->minmap.cell_px_h)));
	start.x = (int)(round(sprite->start.x * (double)(cub->minmap.cell_px_w)));
	end.y = (int)(round(sprite->end.y * (double)(cub->minmap.cell_px_h)));
	end.x = (int)(round(sprite->end.x * (double)(cub->minmap.cell_px_w)));
	player.y = (int)(round(cub->player.y * (double)(cub->minmap.cell_px_h)));
	player.x = (int)(round(cub->player.x * (double)(cub->minmap.cell_px_w)));
	draw_line(start, end, &cub->minmap.minimap, fov_color);
	if (!(cub->player.x == sprite->mid.x && cub->player.y == sprite->mid.y))
	{
		fov_color = argb_to_int(0, 255, 0, 0);
		draw_line(player, start, &cub->minmap.minimap, fov_color);
		fov_color = argb_to_int(0, 0, 0, 255);
		draw_line(player, end, &cub->minmap.minimap, fov_color);
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

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub3d_bonus.h"
#include "libft.h"

int	init_window(t_cub *cub)
{
	int	width;
	int	height;

	mlx_get_screen_size(cub->mlx, &width, &height);
	if (width < cub->width)
		cub->width = width;
	if (height < cub->height)
		cub->height = height;
	cub->win = mlx_new_window(cub->mlx, cub->width, cub->height, "cub3d");
	cub->draw_buf = (char *)malloc(cub->height);
	cub->health.health = 99;
	cub->health.height = (int)(10.0 / 100 * cub->height);
	cub->health.width = (int)(30.0 / 100 * cub->width);
	cub->health.border = (cub->health.height > 2 && cub->health.width > 2) + (int)(10.0 / 100 * cub->health.height);
	cub->health.border_color = argb_to_int(0, 161, 155, 27);
	cub->health.pos.x = 0;
	cub->health.pos.y = cub->height - cub->health.height - 1;
	if (cub->health.height > 0 && cub->health.width > 0)
	{
		cub->health.img.img = mlx_new_image(cub->mlx, cub->health.width, cub->health.height);
		if (!cub->health.img.img)
			return (-1);
		cub->health.img.addr = mlx_get_data_addr(cub->health.img.img, &cub->health.img.bpp, &cub->health.img.len, &cub->health.img.end);
	}
	printf("Health bar: %d health, %d pixel height , %d pixel_width, %d border width, pos y %d/ %d cub height\n", cub->health.health, cub->health.height, cub->health.width, cub->health.border, cub->health.pos.y, cub->height);
	if (!cub->win || !cub->draw_buf)
		return (-1);
	else
		return (0);
}

void	init_sprites_dist(t_sprite **sprites, t_cub *cub)
{
	int	i;

	i = 0;
	ft_memset(cub->draw_buf, 0, cub->height);
	while (sprites && sprites[i])
	{
		sprites[i]->mid.dir = -1.0;
		i++;
	}
}

void	init_sprites(t_sprite **sprites, t_cub *cub)
{
	int		i;
	t_pos	angle;
	t_pos	tmp;
	double	rad;

	i = 0;
	while (sprites && sprites[i])
	{
		angle.x = sprites[i]->mid.x - cub->player.x;
		angle.y = sprites[i]->mid.y - cub->player.y;
		sprites[i]->rad = angle.y / angle.x;
		sprites[i]->rad = atan(sprites[i]->rad);
		rad = degree_to_radiant(90) - sprites[i]->rad;
		sprites[i]->start.x = sprites[i]->mid.x + (0.5 * cos(rad));
		sprites[i]->start.y = sprites[i]->mid.y - (0.5 * sin(rad));
		sprites[i]->end.x = sprites[i]->mid.x - (0.5 * cos(rad));
		sprites[i]->end.y = sprites[i]->mid.y + (0.5 * sin(rad));
		if (!(cub->player.x <= sprites[i]->mid.x))
		{
			tmp = sprites[i]->start;
			sprites[i]->start = sprites[i]->end;
			sprites[i]->end = tmp;
		}
		i++;
	}
}

void	sort_sprite_tab(t_sprite **sprites)
{
	int			i;
	int			j;
	int			stop;
	t_sprite	*tmp;

	i = 0;
	while (sprites && sprites[i] && sprites[i])
	{
		j = 0;
		stop = 0;
		while (sprites && sprites[j] && sprites[j] && sprites[j + 1])
		{
			if (sprites[j]->mid.dir > sprites[j + 1]->mid.dir)
			{
				stop = 1;
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
			}
			j++;
		}
		if (!stop)
			break ;
		i++;
	}
}

void	refresh_healthbar(t_health *health)
{
	int	x;
	int	y;
	int	red;

	y = health->border;
	red = argb_to_int(0, 255, 0, 0);
	while (y < health->height - health->border)
	{
		x = health->border;
		while (x < health->width - health->border)
		{
			if (x - health->border < (int)((float)(health->health) / 100 * (health->width - 2 * health->border)))
				my_pixel_put(&health->img, x, y, red);
			else
				my_pixel_put(&health->img, x, y, 0);
			x++;
		}
		y++;
	}
}

void	init_healthbar(t_health *health)
{
	int	x;
	int	y;

	y = 0;
	while (y < health->height)
	{
		x = 0;
		while (x < health->border)
		{
			my_pixel_put(&health->img, x, y, health->border_color);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < health->height)
	{
		x = health->width - health->border;
		while (x < health->width)
		{
			my_pixel_put(&health->img, x, y, health->border_color);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < health->border)
	{
		x = health->border;
		while (x < health->width - health->border)
		{
			my_pixel_put(&health->img, x, y, health->border_color);
			x++;
		}
		y++;
	}
	y = health->height - health->border;
	while (y < health->height)
	{
		x = health->border;
		while (x < health->width - health->border)
		{
			my_pixel_put(&health->img, x, y, health->border_color);
			x++;
		}
		y++;
	}
}

int	prepare_run(t_cub *cub)
{
	if (init_window(cub) == -1)
	{
		free_cub(cub);
		return (return_error("ERROR: Couldn't create the window\n", -1));
	}
	cub->ray.screen_dist = get_screen_dist(cub->width);
	if (cub->health.img.img)
	{
		init_healthbar(&cub->health);
		refresh_healthbar(&cub->health);
	}
	if (mini_map_to_img(cub) == -1)
		printf("The screen is too small to draw minimap\n");
	return (0);
}

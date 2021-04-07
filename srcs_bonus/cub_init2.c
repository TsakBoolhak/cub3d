/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:04:46 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:04:47 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	prepare_run(t_cub *cub)
{
	if (init_window(cub) == -1)
	{
		free_cub(cub);
		return (return_error("ERROR: Couldn't create the window\n", -1));
	}
	cub->ray.screen_dist = get_screen_dist(cub->width);
	if (mini_map_to_img(cub) == -1)
		printf("The screen is too small to draw minimap\n");
	return (0);
}

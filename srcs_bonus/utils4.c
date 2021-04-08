/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:49:35 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 20:49:38 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"

void	init_next_step(t_coord *vect, t_pos *next, t_pos *play, t_cub *cub)
{
	vect->x = (next->x > play->x);
	vect->y = (next->y > play->y);
	if (next->x < 1.25)
		next->x = 1.25;
	else if (next->x >= (double)(cub->map_w) - 1.25)
		next->x = (double)(cub->map_w) - 1.25;
	if (next->y < 1.25)
		next->y = 1.25;
	else if (next->y >= (double)(cub->map_w) - 1.25)
		next->y = (double)(cub->map_w) - 1.25;
}

void	check_step_collide(t_pos *next, t_pos *play, t_coord vect, t_cub *cub)
{
	char	c;

	c = cub->map[(int)(next->y)][(int)(next->x)];
	if (ft_strchr(" 12", c))
	{
		if ((int)(play->x) != (int)(next->x))
		{
			if (vect.x)
				next->x = (double)((int)(play->x) + 0.75);
			else
				next->x = (double)((int)(play->x) + 0.25);
		}
		if ((int)(play->y) != (int)(next->y))
		{
			if (vect.y)
				next->y = (double)((int)(play->y) + 0.75);
			else
				next->y = (double)((int)(play->y) + 0.25);
		}
	}
}

void	check_up_n_down(t_pos *next_step, int dir, t_cub *cub)
{
	char	c;
	double	dist;

	if (dir == -1)
		dist = 0.25;
	else
		dist = 0.75;
	c = cub->map[(int)(next_step->y) + dir][(int)(next_step->x)];
	if (ft_strchr(" 12", c))
		next_step->y = (int)(next_step->y) + dist;
	if (next_step->x < (int)(next_step->x) + 0.25)
	{
		c = cub->map[(int)(next_step->y) + dir][(int)(next_step->x) - 1];
		if (ft_strchr(" 12", c))
			next_step->y = (int)(next_step->y) + dist;
	}
	else if (next_step->x > (int)(next_step->x) + 0.75)
	{
		c = cub->map[(int)(next_step->y) + dir][(int)(next_step->x) + 1];
		if (ft_strchr(" 12", c))
			next_step->y = (int)(next_step->y) + dist;
	}
}

void	set_next_step(t_pos *next_step, t_pos *player, t_cub *cub)
{
	char	c;
	t_coord	vector;

	init_next_step(&vector, next_step, player, cub);
	check_step_collide(next_step, player, vector, cub);
	if (next_step->x < (int)(next_step->x) + 0.25)
	{
		c = cub->map[(int)(next_step->y)][(int)(next_step->x) - 1];
		if (ft_strchr(" 12", c))
			next_step->x = (int)(next_step->x) + 0.25;
	}
	else if (next_step->x > (int)(next_step->x) + 0.75)
	{
		c = cub->map[(int)(next_step->y)][(int)(next_step->x) + 1];
		if (ft_strchr(" 12", c))
			next_step->x = (int)(next_step->x) + 0.75;
	}
	if (next_step->y < (int)(next_step->y) + 0.25)
		check_up_n_down(next_step, -1, cub);
	else if (next_step->y > (int)(next_step->y) + 0.75)
		check_up_n_down(next_step, 1, cub);
}

void	draw_gun(int x, t_cub *cub)
{
	int		gwidth;
	int		gheight;
	t_coord	gun;
	int		y;
	int		color;

	gwidth = cub->width / 3;
	gun.x = cub->width / 2 - (gwidth / 2);
	gun.y = gun.x + gwidth;
	if (x < gun.x || x > gun.y)
		return ;
	gheight = cub->height / 2;
	y = cub->height - gheight;
	while (y < cub->height)
	{
		color = get_gun_pixel(x, y, gheight, cub);
		if (color)
			my_pixel_put(&cub->screen, x, y, color);
		y++;
	}
}

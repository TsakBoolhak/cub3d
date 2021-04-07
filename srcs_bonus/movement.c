/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:07:04 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:07:08 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include <mlx.h>

void	set_step_increm(t_pos step, t_pos *increm, t_cub *cub)
{
	if (step.dir <= 90)
	{
		increm->x = step.dir / 90;
		increm->y = (1 - increm->x) * -1;
	}
	else if (step.dir <= 180)
	{
		increm->x = 1 - ((step.dir - 90) / 90);
		increm->y = 1 - increm->x;
	}
	else if (step.dir <= 270)
	{
		increm->x = ((step.dir - 180) / 90) * -1;
		increm->y = 1 + increm->x;
	}
	else
	{
		increm->x = (1.0 - ((step.dir - 270) / 90)) * -1;
		increm->y = (1.0 + increm->x) * -1;
	}
	increm->x *= cub->movespeed;
	increm->y *= cub->movespeed;
}

void	set_next_step(t_pos next_step, t_pos *player, t_cub *cub)
{
	char	c;
	t_coord	vector;

	vector.x = (next_step.x > player->x);
	vector.y = (next_step.y > player->y);
	if (next_step.x < 1.15)
		next_step.x = 1.15;
	else if (next_step.x >= (double)(cub->map_w) - 1.15)
		next_step.x = (double)(cub->map_w) - 1.15;
	if (next_step.y < 1.15)
		next_step.y = 1.15;
	else if (next_step.y >= (double)(cub->map_w) - 1.15)
		next_step.y = (double)(cub->map_w) - 1.15;
	c = cub->map[(int)(next_step.y)][(int)(next_step.x)];
	if (ft_strchr(" 12", c))
	{
		if ((int)(player->x) != (int)(next_step.x))
		{
			if (vector.x)
				next_step.x = (double)((int)(player->x) + 0.85);
			else
				next_step.x = (double)((int)(player->x) + 0.15);
		}
		if ((int)(player->y) != (int)(next_step.y))
		{
			if (vector.y)
				next_step.y = (double)((int)(player->y) + 0.85);
			else
				next_step.y = (double)((int)(player->y) + 0.15);
		}
	}
	if (next_step.x < (int)(next_step.x) + 0.15)
	{
		c = cub->map[(int)(next_step.y)][(int)(next_step.x) - 1];
		if (ft_strchr(" 12", c))
			next_step.x = (int)(next_step.x) + 0.15;
	}
	else if (next_step.x > (int)(next_step.x) + 0.85)
	{
		c = cub->map[(int)(next_step.y)][(int)(next_step.x) + 1];
		if (ft_strchr(" 12", c))
			next_step.x = (int)(next_step.x) + 0.85;
	}
	if (next_step.y < (int)(next_step.y) + 0.15)
	{
		c = cub->map[(int)(next_step.y) - 1][(int)(next_step.x)];
		if (ft_strchr(" 12", c))
			next_step.y = (int)(next_step.y) + 0.15;
		if (next_step.x < (int)(next_step.x) + 0.15)
		{
			c = cub->map[(int)(next_step.y) - 1][(int)(next_step.x) - 1];
			if (ft_strchr(" 12", c))
				next_step.y = (int)(next_step.y) + 0.15;
		}
		else if (next_step.x > (int)(next_step.x) + 0.85)
		{
			c = cub->map[(int)(next_step.y) - 1][(int)(next_step.x) + 1];
			if (ft_strchr(" 12", c))
				next_step.y = (int)(next_step.y) + 0.15;
		}
	}
	else if (next_step.y > (int)(next_step.y) + 0.85)
	{
		c = cub->map[(int)(next_step.y) + 1][(int)(next_step.x)];
		if (ft_strchr(" 12", c))
			next_step.y = (int)(next_step.y) + 0.85;
		if (next_step.x < (int)(next_step.x) + 0.15)
		{
			c = cub->map[(int)(next_step.y) + 1][(int)(next_step.x) - 1];
			if (ft_strchr(" 12", c))
				next_step.y = (int)(next_step.y) + 0.85;
		}
		else if (next_step.x > (int)(next_step.x) + 0.85)
		{
			c = cub->map[(int)(next_step.y) + 1][(int)(next_step.x) + 1];
			if (ft_strchr(" 12", c))
				next_step.y = (int)(next_step.y) + 0.85;
		}
	}
	player->x = next_step.x;
	player->y = next_step.y;
}

void	move_advance(t_cub *cub, int forward, int side)
{
	t_pos	step;
	t_pos	increm;

	step.dir = cub->player.dir;
	if (side)
		step.dir += 90;
	if (!forward)
		step.dir += 180;
	if (step.dir >= 360)
		step.dir -= 360;
	set_step_increm(step, &increm, cub);
	step.x = cub->player.x + increm.x;
	step.y = cub->player.y + increm.y;
	set_next_step(step, &cub->player, cub);
}

void	rotate_dir(t_cub *cub, int direction)
{
	double	rot_speed;

	rot_speed = cub->width / 15 + 1;
	rot_speed *= cub->ray.angle_increm;
	cub->player.dir += (rot_speed * direction);
	if (cub->player.dir < 0.0)
		cub->player.dir += 360.0;
	else if (cub->player.dir >= 360.0)
		cub->player.dir -= 360.0;
}

int	handle_keypress(int key, void *cub_ptr)
{
	t_cub	*cub;

	cub = (t_cub *)cub_ptr;
	if (key == 65307)
		mlx_loop_end(cub->mlx);
	if (key == 65361 || key == 97)
		cub->action.rotate_left = 1;
	if (key == 65363 || key == 101)
		cub->action.rotate_right = 1;
	if (key == 65362 || key == 122)
		cub->action.move_forward = 1;
	if (key == 65364 || key == 115)
		cub->action.move_backward = 1;
	if (key == 100)
		cub->action.move_right = 1;
	if (key == 113)
		cub->action.move_left = 1;
	return (0);
}

int	handle_keyrelease(int key, void *cub_ptr)
{
	t_cub	*cub;

	cub = (t_cub *)cub_ptr;
	if (key == 65361 || key == 97)
		cub->action.rotate_left = 0;
	if (key == 65363 || key == 101)
		cub->action.rotate_right = 0;
	if (key == 65362 || key == 122)
		cub->action.move_forward = 0;
	if (key == 65364 || key == 115)
		cub->action.move_backward = 0;
	if (key == 100)
		cub->action.move_right = 0;
	if (key == 113)
		cub->action.move_left = 0;
	return (0);
}

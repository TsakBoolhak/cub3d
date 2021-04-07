/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:02:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:02:42 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
	if ((int)step.x > 0 && (int)step.x < cub->map_w - 1)
		cub->player.x = step.x;
	if ((int)step.y > 0 && (int)step.y < cub->map_h - 1)
		cub->player.y = step.y;
}

void	rotate_dir(t_cub *cub, int direction)
{
	double	rot_speed;

	rot_speed = cub->width / 10 + 1;
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

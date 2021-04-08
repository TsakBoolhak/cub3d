/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:07:56 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:07:57 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d_bonus.h"

void	set_shadows(int *color, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = (*color & 0xFF0000) * ratio;
	g = (*color & 0xFF00) * ratio;
	b = (*color & 0xFF) * ratio;
	*color = 0xFF000000 | (r & 0xFF0000) | (g & 0xFF00) | (b & 0xFF);
}

void	check_step(t_coord vect, t_pos *step, t_pos *increm, t_cub *cub)
{
	t_pos	player;

	player = cub->player;
	if ((vect.x && step->x < player.x) || (vect.y && step->y < player.y)
		|| (!vect.x && step->x > player.x) || (!vect.y && step->y > player.y))
	{
		cub->movespeed = 0.25;
		set_step_increm(*step, increm, cub);
		step->x = cub->player.x + increm->x;
		step->y = cub->player.y + increm->y;
		set_next_step(step, &cub->player, cub);
	}
}

void	check_actions(t_cub *cub)
{
	if (cub->action.sprint)
		cub->movespeed = 0.375;
	else
		cub->movespeed = 0.25;
	if (cub->action.rotate_left)
		rotate_dir(cub, -1);
	if (cub->action.rotate_right)
		rotate_dir(cub, 1);
	if (cub->action.move_forward)
		move_advance(cub, 1, 0);
	if (cub->action.move_backward)
		move_advance(cub, 0, 0);
	if (cub->action.move_right)
		move_advance(cub, 1, 1);
	if (cub->action.move_left)
		move_advance(cub, 0, 1);
}

int	render_frame(void *cub_ptr)
{
	t_cub	*cub;
	int		player_color;

	cub = (t_cub *)cub_ptr;
	check_actions(cub);
	cub->ray.fov_angle = cub->player.dir - FOV / 2.0;
	if (cub->ray.fov_angle < 0.0)
		cub->ray.fov_angle = 360.0 + cub->ray.fov_angle;
	cub->ray.angle_increm = FOV / cub->width;
	if (cub->minmap.minimap.img)
		mlx_destroy_image(cub->mlx, cub->minmap.minimap.img);
	mini_map_to_img(cub);
	raycast_loop(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	if (cub->minmap.minimap.img)
	{
		player_color = argb_to_int(0, 255, 0, 0);
		draw_pos_to_map(&cub->minmap, cub, cub->player, player_color);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->minmap.minimap.img, 0, 0);
	}
	return (0);
}

int	run_cub(t_cub *cub)
{
	t_data	*img;

	if (prepare_run(cub) < 0)
		return (-1);
	cub->movespeed = 0.20;
	img = &cub->screen;
	img->img = mlx_new_image(cub->mlx, cub->width, cub->height);
	if (!img->img)
	{
		free_cub(cub);
		return (return_error("ERROR: Couldnt create the game render\n", -1));
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	mlx_loop_hook(cub->mlx, &render_frame, cub);
	mlx_hook(cub->win, 2, 1L << 0, &handle_keypress, cub);
	mlx_hook(cub->win, 3, 1L << 1, &handle_keyrelease, cub);
	mlx_hook(cub->win, 33, 1L << 17, &mlx_loop_end, cub->mlx);
	mlx_loop(cub->mlx);
	free_cub(cub);
	return (0);
}

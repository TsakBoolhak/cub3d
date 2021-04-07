/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:03:49 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 14:03:50 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"

void	check_actions(t_cub *cub)
{
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

	cub = (t_cub *)cub_ptr;
	check_actions(cub);
	cub->ray.fov_angle = cub->player.dir - FOV / 2.0;
	if (cub->ray.fov_angle < 0.0)
		cub->ray.fov_angle = 360.0 + cub->ray.fov_angle;
	cub->ray.angle_increm = FOV / cub->width;
	raycast_loop(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	return (0);
}

int	run_cub(t_cub *cub)
{
	t_data	*img;

	if (prepare_run(cub) < 0)
		return (-1);
	img = &cub->screen;
	img->img = mlx_new_image(cub->mlx, cub->width, cub->height);
	if (!img->img)
	{
		free_cub(cub);
		return (return_error("ERROR: Couldnt create the game render\n", -1));
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	cub->movespeed = 0.25;
	mlx_loop_hook(cub->mlx, &render_frame, cub);
	mlx_hook(cub->win, 2, 1L << 0, &handle_keypress, cub);
	mlx_hook(cub->win, 3, 1L << 1, &handle_keyrelease, cub);
	mlx_hook(cub->win, 33, 1L << 17, &mlx_loop_end, cub->mlx);
	mlx_loop(cub->mlx);
	free_cub(cub);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:58:19 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 13:59:05 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H
# include <stdint.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		height;
	int		end;
}t_data;

typedef struct s_coord
{
	int	x;
	int	y;
}t_coord;

typedef struct s_pos
{
	double	x;
	double	y;
	double	dir;
}t_pos;

typedef struct s_minimap
{
	t_data	minimap;
	int		map_px_w;
	int		map_px_h;
	int		cell_px_w;
	int		cell_px_h;
}t_minimap;

typedef struct s_ray
{
	double	rad;
	double	fov_angle;
	double	angle_increm;
	double	screen_dist;
	double	wall_h;
	double	fish;
	double	hit_dist;
	t_coord	vect;
	t_pos	hit;
	int		side;
	double	shadow_ratio;
}t_ray;

typedef struct s_action
{
	int	rotate_left;
	int	rotate_right;
	int	move_right;
	int	move_left;
	int	move_forward;
	int	move_backward;
	int	sprint;
	int	exit;
}t_action;

typedef struct s_sprite
{
	int		true_sprite_h;
	int		side;
	int		sprite_h;
	t_pos	mid;
	t_pos	start;
	t_pos	end;
	t_pos	hit;
	double	rad;
	t_coord	coord;
}t_sprite;

typedef struct s_bmp
{
	char		bmpsign[2];
	uint32_t	file_size;
	uint32_t	reserved;
	uint32_t	pixel_offset;
	uint32_t	header_size;
	int32_t		width;
	int32_t		height;
	uint16_t	color_planes;
	uint16_t	color_depth;
	uint32_t	compress;
	uint32_t	raw_bmp_size;
	int32_t		horiz_res;
	int32_t		vert_res;
	uint32_t	color_table;
	uint32_t	important_colors;
}__attribute__((__packed__))t_bmp;

typedef struct s_cub
{
	int			width;
	int			height;
	int			floor_rgb;
	int			ceil_rgb;
	int			map_w;
	int			map_h;
	t_data		north;
	t_data		south;
	t_data		east;
	t_data		west;
	t_data		sprite;
	t_pos		player;
	t_sprite	**sprites;
	t_minimap	minmap;
	t_data		screen;
	t_data		gun;
	t_ray		ray;
	t_action	action;
	int			true_wall_h;
	double		movespeed;
	char		*draw_buf;
	char		**map;
	void		*mlx;
	void		*win;
}t_cub;

#endif

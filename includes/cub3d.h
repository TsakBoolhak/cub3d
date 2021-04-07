/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:44:44 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 20:44:46 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stddef.h>
# include "structures.h"

# define FOV 60.0

/*
***cub_init.c
*/
void	free_pos_tab(t_sprite **tab);
int		cub_init(t_cub *cub);
void	free_cub(t_cub *cub);
int		map_init(int fd, char **line, t_cub *cub);
int		map_adjust(t_cub *cub);

/*
***cub_init2.c
*/
int		init_window(t_cub *cub);
void	init_sprites_dist(t_sprite **sprites, t_cub *cub);
void	init_sprites(t_sprite **sprites, t_cub *cub);
void	sort_sprite_tab(t_sprite **sprites);
int		prepare_run(t_cub *cub);

/*
***generate_bmp.c.c
*/
void	init_header(t_bmp *bmp, t_cub *cub);
void	get_first_image(t_cub *cub);
int		write_into_bmp(int fd, t_bmp *bmp, t_cub *cub);
int		generate_bmp_file(t_cub *cub, char *save);

/*
***parser.c
*/
int		check_elem(char *line, int elem, t_cub *cub, int *elements);
int		check_elements(int *elements);
int		elements_parser(int fd, char **line, t_cub *cub);
int		map_parser(int fd, char **line, t_cub *cub);
int		parser(int ac, char *av[], t_cub *cub);

/*
***parser_elements.c
*/
int		set_resolution(char *line, t_cub *cub);
int		set_texture(char *line, int elem, t_cub *cub);
int		check_colour_values(char **tab);
int		set_colour(char *line, int elem, t_cub *cub);
int		set_elem(char *line, t_cub *cub, int *elements);

/*
***parser_map.c
*/
int		check_around_cell(int x, int y, t_cub *cub);
void	set_spawn(int x, int y, t_cub *cub);
int		set_sprite_position(int x, int y, t_cub *cub);
int		ft_check_map_cell(int x, int y, t_cub *cub, int *spawn);
int		map_is_valid(t_cub *cub);

/*
***utils.c
*/
int		return_error(char *str, int ret);
char	**ft_add_str_to_tab(char **tab, char *line);
size_t	ft_count_char_in_str(const char *s, int c);
int		ft_strischarset(char *str, char *charset);
int		ft_strisdigit(char *str);

/*
***utils2.c
*/
int		rgb_to_r(int rgb);
int		rgb_to_g(int rgb);
int		rgb_to_b(int rgb);
int		argb_to_int(int a, int r, int g, int b);
int		check_overflow(char *nb);

/*
***utils3.c
*/
double	degree_to_radiant(double degree);
int		get_x_vector(double dir);
int		get_y_vector(double dir);
double	get_rad_for_x_cross(double dir);
double	get_rad_for_y_cross(double dir);

/*
***draw.c
*/
void	my_pixel_put(t_data *data, int x, int y, int color);
void	draw_ceil_or_floor(int x, int *y, t_cub *cub, int floor);
void	draw_wall(int x, int *y, int wall_h, t_cub *cub);
void	draw_sprites(int x, t_cub *cub);
void	draw_wall_to_screen(int x, t_cub *cub);

/*
***ray_intersect.c
*/
t_pos	get_next_intersect(t_pos origin, double rad, t_coord vect, int loop);
t_pos	get_first_x_intersect(t_pos origin, double rad, t_coord vect);
t_pos	get_first_y_intersect(t_pos origin, double rad, t_coord vect);
void	check_for_sprite(t_pos *pos, t_coord tmp, t_cub *cub, int loop);
void	intersect_loop(t_pos *pos, t_cub *cub, int loop);

/*
***movement.c
*/
void	set_step_increm(t_pos step, t_pos *increm, t_cub *cub);
void	move_advance(t_cub *cub, int forward, int side);
void	rotate_dir(t_cub *cub, int direction);
int		handle_keypress(int key, void *cub_ptr);
int		handle_keyrelease(int key, void *cub_ptr);

/*
***raycast.c
*/
t_pos	closest_hit(t_pos orig, t_pos x_pos, t_pos y_pos, t_cub *cub);
t_pos	get_wall_hit(t_pos orig, double fov_angle, t_cub *cub);
double	get_screen_dist(int width);
double	get_wall_height(double fisheye_correct, t_cub *cub);
void	raycast_loop(t_cub *cub);

/*
***raycast_sprite.c
*/
double	get_distance(t_pos pos1, t_pos pos2);
int		set_angle(t_pos player, t_sprite *sprite, t_pos *hit, t_pos *angle);
int		set_sprite(t_cub *cub, t_sprite *sprite, t_pos *hit, t_pos *sprite_hit);
void	set_sprite_dist(t_coord	sprite, t_pos *hit, t_cub *cub);
int		get_sprite_height(t_cub *cub, t_sprite *sprite);

/*
***get_pixels.c
*/
int		get_sprite_pixel(int *y, t_sprite *sprite, t_cub *cub);
char	*get_texture_pixel(int *y, t_cub *cub);
t_data	get_texture_data(t_cub *cub, t_pos *ratio);

/*
***run_cub.c
*/
void	check_actions(t_cub *cub);
int		render_frame(void *cub_ptr);
int		run_cub(t_cub *cub);

#endif

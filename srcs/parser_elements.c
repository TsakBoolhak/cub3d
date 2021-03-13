/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:53:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/02/03 18:14:36 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <mlx.h>
#include <stdlib.h>

int	set_resolution(char *line, t_cub *cub)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (!tab)
		return (return_error("MEM ERROR: Couldn't allocate memory\n", 0));
	if (ft_tab_size(tab) != 2)
	{
		ft_free_tab((void **)tab);
		return (return_error("PARSING ERROR: Wrong resolution\n", 0));
	}
	cub->width = ft_atoi(tab[0]);
	cub->height = ft_atoi(tab[1]);
	if (!ft_strisdigit(tab[0]) || !ft_strisdigit(tab[1])
		|| !cub->width || !cub->height)
	{
		ft_free_tab((void **)tab);
		return (return_error("PARSING ERROR: Wrong resolution\n", 0));
	}
	if (ft_strlen(tab[0]) > 5 || cub->width > 15360)
		cub->width = 15360;
	if (ft_strlen(tab[1]) > 4 || cub->height > 8640)
		cub->height = 8640;
	ft_free_tab((void **)tab);
	return (1);
}

int	set_texture(char *line, int elem, t_cub *cub)
{
	char	*trimmed;
	t_data	tex;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (return_error("MEM ERROR: Couldn't allocate memory\n", 0));
	tex.img = mlx_xpm_file_to_image(cub->mlx, trimmed, &tex.len, &tex.height);
	free(trimmed);
	if (!tex.img)
		return (return_error("PARSING ERROR: Couldn't import texture\n", 0));
	tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.len, &tex.end);
	if (elem == 3)
		cub->sprite = tex;
	else if (elem == 4)
		cub->north = tex;
	else if (elem == 5)
		cub->south = tex;
	else if (elem == 6)
		cub->east = tex;
	else if (elem == 7)
		cub->west = tex;
	return (1);
}

int	check_colour_values(char **tab)
{
	int		i;
	char	*value;
	int		rgb[3];

	i = 0;
	while (i < 3)
	{
		value = ft_strtrim(tab[i], " ");
		if (!value)
			return (return_error("MEM ERROR: Couldn't allocate memory\n", -1));
		if (ft_strlen(value) > 3 || !ft_strisdigit(value))
		{
			free(value);
			return (return_error("PARSING ERROR: Wrong color value\n", -1));
		}
		rgb[i] = ft_atoi(value);
		free(value);
		if (rgb[i] > 255)
			return (return_error("PARSING ERROR: Wrong color value\n", -1));
		i++;
	}
	return (argb_to_int(0, rgb[0], rgb[1], rgb[2]));
}

int	set_colour(char *line, int elem, t_cub *cub)
{
	char	**tab;
	int		color;

	if (ft_count_char_in_str(line, ',') != 2)
		return (return_error("PARSING ERROR: Wrong color line\n", 0));
	tab = ft_split(line, ',');
	if (ft_tab_size(tab) != 3)
	{
		ft_free_tab((void *)tab);
		return (return_error("PARSING ERROR: Wrong color line\n", 0));
	}
	color = check_colour_values(tab);
	if (!elem)
		cub->floor_rgb = color;
	else
		cub->ceil_rgb = color;
	ft_free_tab((void **)tab);
	if (color < 0)
		return (0);
	return (1);
}

int	set_elem(char *line, t_cub *cub, int *elements)
{
	int	elem;

	if (!*line)
		return (8);
	while (*line == ' ')
		line++;
	if (!ft_strncmp(line, "F", 1))
		elem = 0;
	else if (!ft_strncmp(line, "C", 1))
		elem = 1;
	else if (!ft_strncmp(line, "R", 1))
		elem = 2;
	else if (!ft_strncmp(line, "NO", 2))
		elem = 4;
	else if (!ft_strncmp(line, "SO", 2))
		elem = 5;
	else if (!ft_strncmp(line, "S", 1))
		elem = 3;
	else if (!ft_strncmp(line, "EA", 2))
		elem = 6;
	else if (!ft_strncmp(line, "WE", 2))
		elem = 7;
	else
		return (return_error("PARSING ERROR: Unknown parameter's id\n", -1));
	return (check_elem(line, elem, cub, elements));
}

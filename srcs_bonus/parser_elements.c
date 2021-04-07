/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:47:40 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 20:47:41 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include <mlx.h>
#include <stdlib.h>

int	set_resolution(char *line, t_cub *cub)
{
	char	**tab;
	int		ret;

	tab = ft_split(line, ' ');
	ret = 1;
	if (!tab)
		ret = return_error("Error\nCouldn't allocate memory\n", 0);
	if (ft_tab_size(tab) != 2)
		ret = return_error("Error\nResolution must contain 2 values\n", 0);
	else
	{
		cub->width = ft_atoi(tab[0]);
		cub->height = ft_atoi(tab[1]);
		if (!ft_strisdigit(tab[0]) || !ft_strisdigit(tab[1])
			|| cub->width < 1 || cub->height < 1)
		{
			ft_putstr_fd("Error\nResolution's values must be numbers", 2);
			ret = return_error(" greater than zero\n", 0);
		}
		else if (check_overflow(tab[0]) || check_overflow(tab[1]))
			ret = return_error("Error\nResolution's value too large\n", 0);
	}
	ft_free_tab((void **)tab);
	return (ret);
}

int	set_texture(char *line, int elem, t_cub *cub)
{
	char	*trimmed;
	t_data	tex;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (return_error("Error\nCouldn't allocate memory\n", 0));
	tex.img = mlx_xpm_file_to_image(cub->mlx, trimmed, &tex.len, &tex.height);
	free(trimmed);
	if (!tex.img)
		return (return_error("Error\nCouldn't import texture\n", 0));
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
			return (return_error("Error\nCouldn't allocate memory\n", -1));
		else if (!*value)
		{
			free(value);
			return (return_error("Error\nMissing value in color\n", -1));
		}
		rgb[i] = ft_atoi(value);
		if (ft_strlen(value) > 3 || !ft_strisdigit(value) || rgb[i++] > 255)
		{
			free(value);
			return (return_error("Error\nWrong value(s) for color's rgb", -1));
		}
		free(value);
	}
	return (argb_to_int(0, rgb[0], rgb[1], rgb[2]));
}

int	set_colour(char *line, int elem, t_cub *cub)
{
	char	**tab;
	int		color;

	if (ft_count_char_in_str(line, ',') != 2)
		return (return_error("Error\nCheck the commas in color's line\n", 0));
	tab = ft_split(line, ',');
	if (ft_tab_size(tab) != 3)
	{
		ft_free_tab((void *)tab);
		ft_putstr_fd("Error\nColor must contain 3 values, included between", 2);
		return (return_error(" 0 and 255, separated by commas\n", 0));
	}
	color = check_colour_values(tab);
	ft_free_tab((void **)tab);
	if (color < 0)
		return (0);
	if (!elem)
		cub->floor_rgb = color;
	else
		cub->ceil_rgb = color;
	return (1);
}

int	set_elem(char *line, t_cub *cub, int *elements)
{
	int	elem;

	if (!*line)
		return (8);
	while (*line == ' ')
		line++;
	if (!ft_strncmp(line, "F ", 2))
		elem = 0;
	else if (!ft_strncmp(line, "C ", 2))
		elem = 1;
	else if (!ft_strncmp(line, "R ", 2))
		elem = 2;
	else if (!ft_strncmp(line, "S ", 2))
		elem = 3;
	else if (!ft_strncmp(line, "NO ", 3))
		elem = 4;
	else if (!ft_strncmp(line, "SO ", 3))
		elem = 5;
	else if (!ft_strncmp(line, "EA ", 3))
		elem = 6;
	else if (!ft_strncmp(line, "WE ", 3))
		elem = 7;
	else
		return (return_error("Error\nUnknown parameter's id\n", -1));
	return (check_elem(line, elem, cub, elements));
}

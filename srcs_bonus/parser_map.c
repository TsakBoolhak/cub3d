/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:53:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/03/02 21:58:56 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d_bonus.h"
#include <stdlib.h>

int	check_around_cell(int x, int y, t_cub *cub)
{
	if (x < cub->map_w - 1 && !ft_strchr("0123 NEWS", cub->map[y][x + 1]))
		return (return_error("Error\nInvalid character in map\n", -1));
	if (x > 0 && !ft_strchr("0123 NEWS", cub->map[y][x - 1]))
		return (return_error("Error\nInvalid character in map\n", -1));
	if (y < cub->map_h - 1 && !ft_strchr("0123 NEWS", cub->map[y + 1][x]))
		return (return_error("Error\nInvalid character in map\n", -1));
	if (y > 0 && !ft_strchr("0123 NEWS", cub->map[y - 1][x]))
		return (return_error("Error\nInvalid character in map\n", -1));
	if (x < cub->map_w - 1 && !ft_strchr(" 1", cub->map[y][x + 1]))
		return (return_error("Error\nMap is open\n", -1));
	if (x > 0 && !ft_strchr(" 1", cub->map[y][x - 1]))
		return (return_error("Error\nMap is open\n", -1));
	if (y < cub->map_h - 1 && !ft_strchr(" 1", cub->map[y + 1][x]))
		return (return_error("Error\nMap is open\n", -1));
	if (y > 0 && !ft_strchr(" 1", cub->map[y - 1][x]))
		return (return_error("Error\nMap is open\n", -1));
	return (0);
}

void	set_spawn(int x, int y, t_cub *cub)
{
	char	c;

	c = cub->map[y][x];
	cub->player.x = (double)(x) + 0.5;
	cub->player.y = (double)(y) + 0.5;
	if (c == 'N')
		cub->player.dir = 0.0;
	else if (c == 'E')
		cub->player.dir = 90.0;
	else if (c == 'S')
		cub->player.dir = 180.0;
	else if (c == 'W')
		cub->player.dir = 270.0;
}

int	set_sprite_position(int x, int y, t_cub *cub)
{
	t_sprite	**sprites;
	int			i;

	i = 0;
	while (cub->sprites && cub->sprites[i])
		i++;
	sprites = malloc(sizeof(*sprites) * (i + 2));
	if (!sprites)
		return (return_error("Error\nCouldnt allocate memory\n", -1));
	sprites[i + 1] = NULL;
	sprites[i] = (t_sprite *)malloc(sizeof(t_sprite));
	if (!sprites[i])
	{
		free(sprites);
		return (return_error("Error\nCouldnt allocate memory\n", -1));
	}
	sprites[i]->coord.x = x;
	sprites[i]->coord.y = y;
	sprites[i]->mid.x = x + 0.5;
	sprites[i]->mid.y = y + 0.5;
	while (i-- > 0)
		sprites[i] = cub->sprites[i];
	free(cub->sprites);
	cub->sprites = sprites;
	return (0);
}

int	check_door(int x, int y, t_cub *cub)
{
	char	news[4];

	news[0] = (cub->map[y - 1][x] == '1');
	news[1] = (cub->map[y][x + 1] == '1');
	news[2] = (cub->map[y][x - 1] == '1');
	news[3] = (cub->map[y + 1][x] == '1');
	if ((news[0] && news[1]) || (news[0] && news[2]) || (news[0] && !news[3])
		|| (news[1] && news[3]) || (news[1] && !news[2])
		|| (news[2] && news[3]) || (news[2] && !news[1])
		|| (news[3] && !news[0]) || news[0] + news[1] + news[2] + news[3] != 2)
		return return_error("Error\nDoor isn't well placed\n", -1);
	return (0);
}

int	ft_check_map_cell(int x, int y, t_cub *cub, int *spawn)
{
	int	ret;

	ret = 0;
	if (!ft_strchr("0123 NEWS", cub->map[y][x]))
		return (return_error("Error\nInvalid character in map\n", -1));
	else if ((!x || !y || x == cub->map_w - 1 || y == cub->map_h - 1)
		&& cub->map[y][x] != '1' && cub->map[y][x] != ' ')
		return (return_error("Error\nMap is open\n", -1));
	if (cub->map[y][x] == ' ')
		return (check_around_cell(x, y, cub));
	else if (ft_isalpha(cub->map[y][x]))
	{
		if (*spawn)
			return (return_error("Error\nToo many spawn points\n", -1));
		*spawn = 1;
		set_spawn(x, y, cub);
	}
	else if (cub->map[y][x] == '2' || cub->map[y][x] == '3')
		ret = set_sprite_position(x, y, cub);
	if (cub->map[y][x] == '3' && ret != -1)
		ret = check_door(x, y, cub);
	return (ret);
}

int	map_is_valid(t_cub *cub)
{
	int	x;
	int	y;
	int	spawn;

	y = 0;
	spawn = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			if (ft_check_map_cell(x, y, cub, &spawn) < 0)
				return (-1);
			x++;
		}
		y++;
	}
	if (!spawn)
		return (return_error("Error\nThere is no spawn in the map!\n", -1));
	return (0);
}

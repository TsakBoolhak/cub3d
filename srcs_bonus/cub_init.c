/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:46:01 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 20:46:03 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include <mlx.h>
#include <stdlib.h>

void	free_pos_tab(t_sprite **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	cub_init(t_cub *cub)
{
	t_data	*gun;
	char	*str;

	ft_memset(cub, 0, sizeof(*cub));
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (return_error("Error\nCouldn't allocate memory\n", -1));
	str = "textures/jagpistol.xpm";
	gun = &cub->gun;
	gun->img = mlx_xpm_file_to_image(cub->mlx, str, &gun->len, &gun->height);
	if (!gun->img)
		return (return_error("Error\nCouldn't import gun texture\n", -1));
	gun->addr = mlx_get_data_addr(gun->img, &gun->bpp, &gun->len, &gun->end);
	return (0);
}

void	free_cub(t_cub *cub)
{
	if (cub->north.img)
		mlx_destroy_image(cub->mlx, cub->north.img);
	if (cub->south.img)
		mlx_destroy_image(cub->mlx, cub->south.img);
	if (cub->east.img)
		mlx_destroy_image(cub->mlx, cub->east.img);
	if (cub->west.img)
		mlx_destroy_image(cub->mlx, cub->west.img);
	if (cub->sprite.img)
		mlx_destroy_image(cub->mlx, cub->sprite.img);
	if (cub->map)
		ft_free_tab((void **)(cub->map));
	if (cub->sprites)
		free_pos_tab(cub->sprites);
	if (cub->screen.img)
		mlx_destroy_image(cub->mlx, cub->screen.img);
	free(cub->draw_buf);
	if (cub->minmap.minimap.img)
		mlx_destroy_image(cub->mlx, cub->minmap.minimap.img);
	if (cub->gun.img)
		mlx_destroy_image(cub->mlx, cub->gun.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
}

int	map_init(int fd, char **line, t_cub *cub)
{
	int	ret;
	int	len;

	ret = 1;
	while (ret > 0)
	{
		cub->map_h++;
		len = (int)ft_strlen(*line);
		if (cub->map_w < len)
			cub->map_w = len;
		cub->map = ft_add_str_to_tab(cub->map, *line);
		if (!cub->map)
			return (return_error("Error\nCouldn't allocate memory\n", -1));
		ret = get_next_line(fd, line, 0);
		if (ret < 0)
			return (return_error("Error\nCouldn't read file\n", -1));
		if (!ret)
			break ;
	}
	if (cub->map_w < 3 || cub->map_h < 3)
		return (return_error("Error\nMap is too small to be valid\n", -1));
	else
		return (0);
}

int	map_adjust(t_cub *cub)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	while (cub->map[i])
	{
		len = (int)ft_strlen(cub->map[i]);
		if (len < cub->map_w)
		{
			tmp = (char *)malloc(sizeof(*tmp) * (cub->map_w + 1));
			if (!tmp)
				return (-1);
			ft_memcpy(tmp, cub->map[i], len);
			ft_memset(tmp + len, ' ', cub->map_w - len);
			tmp[cub->map_w] = '\0';
			free(cub->map[i]);
			cub->map[i] = tmp;
		}
		i++;
	}
	return (0);
}

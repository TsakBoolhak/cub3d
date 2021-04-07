/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:46:53 by acabiac           #+#    #+#             */
/*   Updated: 2021/04/07 20:46:54 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include "cub3d_bonus.h"
#include "libft.h"

char	*get_save_path(char *cubpath, t_cub *cub)
{
	int		i;
	int		j;
	char	*savename;

	i = 0;
	j = 0;
	while (cubpath[i])
	{
		if (cubpath[i] == '/')
			j = i + 1;
		i++;
	}
	savename = ft_strjoin("./saves/", &cubpath[j]);
	if (!savename)
	{
		free_cub(cub);
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (NULL);
	}
	i = ft_strlen(savename) - 3;
	ft_memcpy(&savename[i], "bmp", 3);
	return (savename);
}

int	run_save(char *cubpath, t_cub *cub)
{
	int		ret;
	char	*savename;

	savename = get_save_path(cubpath, cub);
	if (!savename)
		return (-1);
	ft_putstr_fd("Generating bitmap file into saves directory.\n", 1);
	ft_putstr_fd("Please wait... ", 1);
	ft_putstr_fd("(The larger the resolution is, the longer it takes)\n", 1);
	ret = generate_bmp_file(cub, savename);
	free(savename);
	free_cub(cub);
	return (ret);
}

int	main(int ac, char *av[])
{
	t_cub	cub;

	if (cub_init(&cub) < 0)
		return (-1);
	if (parser(ac, av, &cub) < 0)
	{
		free_cub(&cub);
		return (-1);
	}
	if (ac == 3)
		return (run_save(av[1], &cub));
	else
		return (run_cub(&cub));
}

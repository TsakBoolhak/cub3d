/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:53:15 by acabiac           #+#    #+#             */
/*   Updated: 2021/02/03 19:08:43 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	check_elem(char *line, int elem, t_cub *cub, int *elements)
{
	int	tag_len;

	tag_len = 1 + (elem > 3);
	if (elements[elem])
		return (return_error("PARSING ERROR: same parameter ID twice\n", -1));
	else if (elem < 2)
	{
		if (!set_colour(line + tag_len, elem, cub))
			return (-1);
	}
	else if (elem > 2)
	{
		if (!set_texture(line + tag_len, elem, cub))
			return (-1);
	}
	else
	{
		if (!set_resolution(line + tag_len, cub))
			return (-1);
	}
	return (elem);
}

int	check_elements(int *elements)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (elements[i] != 1)
			return (0);
		i++;
	}
	return (1);
}

int	elements_parser(int fd, char **line, t_cub *cub)
{
	int		ret;
	int		elements[8];
	int		elem;

	ft_bzero(elements, sizeof(int) * 8);
	ret = 1;
	while (ret > 0)
	{
		if (check_elements(elements))
			return (0);
		ret = get_next_line(fd, line, 0);
		if (ret < 0)
			return (return_error("READ ERROR: couldnt read file\n", -1));
		else if (ret < 1)
			return (-1);
		elem = set_elem(*line, cub, elements);
		if (elem < 0)
			return (-1);
		free(*line);
		*line = NULL;
		if (elem == 8)
			continue ;
		elements[elem]++;
	}
	return (0);
}

int	map_parser(int fd, char **line, t_cub *cub)
{
	if (map_init(fd, line, cub) < 0)
	{
		return (-1);
	}
	else if (map_adjust(cub) < 0)
	{
		return (return_error("MAP_ERROR: Couldn't allocate memory\n", -1));
	}
	else if (map_is_valid(cub) < 0)
	{
		return (-1);
	}
	return (0);
}

int	parser(int ac, char *av[], t_cub *cub)
{
	int		fd;
	char	*line;

	if (ac < 2 || ac > 3)
		return (return_error("INPUT ERROR: Wrong number of arguments\n", -1));
	else if (ac == 3 && ft_strcmp(av[2], "--save"))
		return (return_error("INPUT ERROR: 2nd argument must be --save\n", -1));
	line = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (!line || *(line + 4) != '\0')
		return (return_error("INPUT ERROR: file miss .cub extension\n", -1));
	line = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (return_error("READ ERROR: Could not open file\n", -1));
	if (elements_parser(fd, &line, cub) < 0 || map_parser(fd, &line, cub) < 0)
	{
		if (line)
			free(line);
		get_next_line(fd, NULL, 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

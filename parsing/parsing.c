/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/16 10:56:45 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *is_ext_valid(char *map)
{
	char *ext;

	ext = ft_strnstr(map, ".ber", ft_strlen(map));
	if (ext && ft_strlen(ext) == 4)
		return (NULL);
	else
		return ("Error\nunvalid map extension!");
}

char *is_rectangular(int fd)
{
	char *line;
	int line_size;

	line = get_next_line(fd, 0);
	line_size = ft_strlen(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd, 0);
		if (line && line_size == ft_strlen(line))
			break;
	}
	return (NULL);
}

int	recursion(char **map_data, int x, int y, int *count)
{
	if (map_data[y][x] == '1' || !(*count))
		return ;
	if (map_data[y][x] == 'E' || map_data[y][x] == 'C')
		(*count)--;
	map_data[y][x] = '1';
	recursion(map_data, x - 1, y, count); // left
	recursion(map_data, x, y - 1, count); // down
	recursion(map_data, x + 1, y, count); // right
	recursion(map_data, x, y + 1, count); // up
	if (*count)
		return (false);
	return (true);
}

char	**get_map(int fd)
{

	return (NULL);
}

char	*is_map_valid(char *map)
{
	char	*err;
	t_map_data data;
	int fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		perror_exit("failed to open");
	data.m = get_map(fd);
	data.count = get_conponments(&data);
	if (!recursion(data.m, data.x, data.y, &data.count))
		return (clean_up(data.m), "Error\nunvalid path\n");
	return (NULL);
}

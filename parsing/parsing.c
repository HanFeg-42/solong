/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/18 23:03:44 by hfegrach         ###   ########.fr       */
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

char	**get_map(int fd, t_map_data *data)
{
	char *line;
	char *map;
	char **map_arr;
	char *tmp;
	int P = 0;
	int E = 0;
	int C = 0;
	int line_size;
	data->height = 0;
	int elmt_counter = 0;

	line = get_next_line(fd, 0);
	line_size = ft_strlen(line);
	is_line_wall(line);
	map = ft_strdup("");
	while (line)
	{
		data->height++;
		is_line_valid(line, line_size); // contains only 1 0 E C P M
		check_element(line, 'P', &P, data);
		check_element(line, 'E', &E, data);
		check_element(line, 'C', &C, data);
		tmp = map;
		ft_strjoin(map, line);
		free(tmp);
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	if (!(P == 1 && E == 1 && C > 0))
		(free(map), throw_error("unvalid map\n"));
	map_arr = ft_split(map, '\n');
	is_line_wall(map_arr[data->height - 1]);
	data->count = E + C;
	return (map_arr);
}

void	check_element(char *line, char c, int *character, t_map_data *data)
{
	char *is_exist;

	is_exist = ft_strchr(line, c);
	if (is_exist)
	{
		if (c == 'P' && !(*character))
		{
			(*character) = 1;
			data->x = 
			data->y = data->height;
		}
		else if (c == 'P' && (*character))
			throw_error("unvalid map\n");
		if (c == 'E' && !(*character))
			(*character) = 1;
		else if (c == 'E' && (*character))
			throw_error("unvalid map\n");
		if (c == 'C' && !(*character))
			(*character)++;
	}
}

void	is_line_wall(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			throw_error("unvalid map\n");
		i++;
	}
}

void	is_line_valid(char *line, int size)
{
	int i;
	char emoji[8] = "10PCEM\n";

	i = 0;
	if (line[0] != '1' || line[size - 1] != '\n'
		|| line[size - 2] != '1' || size != ft_strlen(line))
		throw_error("unvalid map\n");
	while (line[i])
	{
		if (!ft_strchr(emoji, line[i]))
			throw_error("unvalid map\n");
		i++;
	}
}

char	*is_map_valid(char *map)
{
	char	*err;
	t_map_data data;
	int fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		perror_exit("failed to open");
	data.m = get_map(fd, &data);
	// data.count = get_conponments(&data);
	if (!recursion(data.m, data.x, data.y, &data.count))
		return (clean_up(data.m), "Error\nunvalid path\n");
	return (NULL);
}

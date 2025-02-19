/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/19 02:17:28 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_map_ext(char *map)
{
	char *ext;
	int	size;

	size = ft_strlen(map);
	ext = ft_strnstr(map, ".ber", size);
	if (!(ext && ft_strlen(ext) == 4 && size > 4))
		throw_error("unvalid map extension!\n");
}

int	recursion(char **map_data, int x, int y, int *count)
{
	if (map_data[y][x] == '1' || !(*count))
		return (false);
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
		map = ft_strjoin(map, line);
		free(tmp);
		free(line);
		line = get_next_line(fd, 0);
	}
	if (!(P == 1 && E == 1 && C > 0))
		(free(map), throw_error("unvalid map: p | e | c chi wahed fihum makaynch\n"));
	map_arr = ft_split(map, '\n');
	free(map);
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
			data->x = ft_strchr_index(line, c);
			data->y = data->height - 1;
		}
		else if (c == 'P' && (*character))
			throw_error("unvalid map: duplicated P\n");
		if (c == 'E' && !(*character))
			(*character) = 1;
		else if (c == 'E' && (*character))
			throw_error("unvalid map: duplicated E\n");
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
		if (line[i + 1] == '\0' && line [i] == '\n')
			break;
		if (line[i] != '1')
			throw_error("unvalid map : check top and bottom walls\n");
		i++;
	}
}

void	is_line_valid(char *line, int size)
{
	int i;
	char emoji[7] = "10PCEM";

	i = 0;
	if (line[size - 1] == '\n')
	{
		if (line[0] != '1' || line[size - 2] != '1' || size != (int)ft_strlen(line))
			throw_error("unvalid map: had line fiha khalal\n");
	}
	else
	{
		if (line[0] != '1' || line[size - 2] != '1' || size - 1 != (int)ft_strlen(line))
			throw_error("unvalid map 3ndk mochkil\n");
	}
	while (line[i + 1])
	{
		if (!ft_strchr(emoji, line[i]))
			throw_error("unvalid map : zdti chi haja\n");
		i++;
	}
}

char	*is_map_valid(char *map, t_solong *var)
{
	t_map_data data;
	int fd;

	check_map_ext(map);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		perror_exit("failed to open");
	data.m = get_map(fd, &data);
	var->map = copy_map(data);
	if (!recursion(data.m, data.x, data.y, &data.count))
		return (print_map(data.m), clean_up(data.m), "unvalid path\n");
	return (clean_up(data.m), NULL);
}

char **copy_map(t_map_data data)
{
	char	**ret;
	int		i;

	// printf("%d\n", data.height);
	// print_map(data.m);
	ret = malloc(sizeof(char *) * (data.height + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (data.m[i])
	{
		ret[i] = ft_strdup(data.m[i]);
		i++;
	}
	ret[i] = NULL;
		// exit(0);
	return (ret);
}

void print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

// .ber   the name of file should be larger than 4 caract...
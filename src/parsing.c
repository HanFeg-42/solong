/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 00:04:15 by hfegrach         ###   ########.fr       */
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
char	**get_map(int fd)
{
	char *line;
	char *join;
	char **map;
	char *tmp;
	size_t size;

	line = get_next_line(fd, 0);
	size = ft_strlen(line);
	join = ft_strdup("");
	while (line)
	{
		tmp = join;
		join = ft_strjoin(join, line);
		free(tmp);
		free(line);
		line = get_next_line(fd, 0);
		if (line && !(size == ft_strlen(line) || size - 1 == ft_strlen(line)))
		{
			free(line);
			free(join);
			throw_error("it is not rectangular!\n");
		}
	}
	free(line);
	map = ft_split(join, '\n');
	free(join);
	return (map);
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
	char emoji[7] = "10PCE";

	i = 0;
	if (size != (int)ft_strlen(line) || line[0] != '1' || line[size - 1] != '1')
		throw_error("unvalid map 3ndk mochkil\n");
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
	data.m = get_map(fd);
	check_map(&data);
	var->map = copy_map(data);
	var->coins = data.count;
	data.count++;
	init_player_position(&data);
	if (!recursion(data.m, data.x, data.y, &data.count))
		return (print_map(data.m), clean_up(data.m), "unvalid path\n");
	return (clean_up(data.m), NULL);
}

char **copy_map(t_map_data data)
{
	char	**ret;
	int		i;

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

void	check_map(t_map_data *data)
{
	is_map_rect(data);
	is_player_valid(data);
	is_collectible_valid(data);
	is_exit_valid(data);
}
void init_player_position(t_map_data *data)
{
	int (x), (y);
	y = 0;
	while (data->m[y])
	{
		x = 0;
		while (data->m[y][x])
		{
			if (data->m[y][x] == 'P')
			{
				data->x = x;
				data->y = y;
			}
			x++;
		}
		y++;
	}
}


void is_map_rect(t_map_data *data)
{
	int i;
	size_t size;

	size = ft_strlen(data->m[0]);
	is_line_wall(data->m[0]);
	i = 1;
	while (data->m[i])
	{
		is_line_valid(data->m[i], size);
		i++;
	}
	data->height = i;
	is_line_wall(data->m[i - 1]);
}

void is_player_valid(t_map_data *data)
{
	int x;
	int y;
	int check = true;

	y = 0;
	while (data->m[y])
	{
		x = 0;
		while (data->m[y][x])
		{
			if (data->m[y][x] == 'P' && check)
				check = false;
			else if (data->m[y][x] == 'P' && !check)
				throw_error("player duplicated\n");
			x++;
		}
		y++;
	}
	if (check)
		throw_error("No player detected\n");
}

void is_exit_valid(t_map_data *data)
{
	int x;
	int y;
	int check = true;

	y = 0;
	while (data->m[y])
	{
		x = 0;
		while (data->m[y][x])
		{
			if (data->m[y][x] == 'E' && check)
				check = false;
			else if (data->m[y][x] == 'E' && !check)
				throw_error("exit duplicated\n");
			x++;
		}
		y++;
	}
	if (check)
		throw_error("No exit detected\n");
}

void is_collectible_valid(t_map_data *data)
{
	int x;
	int y;
	int check = true;
	int count;

	count = 0;
	y = 0;
	while (data->m[y])
	{
		x = 0;
		while (data->m[y][x])
		{
			if (data->m[y][x] == 'C')
			{
				check = false;
				count++;
			}
			x++;
		}
		y++;
	}
	if (check)
		throw_error("No coins detected\n");
	data->count = count;
}



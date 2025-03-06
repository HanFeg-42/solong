/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/06 15:34:11 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	is_map_valid_(t_data *data)
{
	char	**tmp_map;
	int		count;

	open_map_(data);
	get_map_(data);
	check_walls_elemt(data);
	is_player_valid_(data);
	is_collectible_valid_(data);
	is_exit_valid_(data);
	is_enemy_valid_(data);
	tmp_map = copy_map_(*data);
	init_player_exit_pos_(data);
	count = data->coins_count + 1;
	if (!check_path_(tmp_map, data->px, data->py, &count))
	{
		clean_up(tmp_map);
		clean_and_exit(data->map, "unvalid path\n");
	}
	clean_up(tmp_map);
}

void	init_player_exit_pos_(t_data *data)
{
	int (x), (y);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->px = x;
				data->py = y;
			}
			if (data->map[y][x] == 'E')
			{
				data->ex = x;
				data->ey = y;
			}
			x++;
		}
		y++;
	}
}

int	check_path_(char **map_data, int x, int y, int *count)
{
	if (map_data[y][x] == '1' || map_data[y][x] == 'M' || !(*count))
		return (false);
	if (map_data[y][x] == 'E' || map_data[y][x] == 'C')
		(*count)--;
	map_data[y][x] = '1';
	check_path_(map_data, x - 1, y, count);
	check_path_(map_data, x, y - 1, count);
	check_path_(map_data, x + 1, y, count);
	check_path_(map_data, x, y + 1, count);
	if (*count)
		return (false);
	return (true);
}

char	**copy_map_(t_data data)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (data.height + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (data.map[i])
	{
		ret[i] = ft_strdup(data.map[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
void open_map_(t_data *data)
{
	check_map_ext_(data->map_name);
	data->fd = open(data->map_name, O_RDONLY);
	if (data->fd < 0)
		perror_exit("failed to open");
}

void get_map_(t_data *data)
{
	char	*line;
	char	*tmp;

	line = get_next_line(data->fd, 0);
	data->width = ft_strlen(line);
	data->join = ft_strdup("");
	while (line)
	{
		data->height++;
		tmp = data->join;
		data->join = ft_strjoin(data->join, line);
		free(tmp);
		free(line);
		line = get_next_line(data->fd, 0);
		if (line && !(data->width == ft_strlen(line) || data->width - 1 == ft_strlen(line)))
			not_rectang(data, line);
	}
	free(line);
	data->map = ft_split(data->join, '\n');
	free(data->join);
}

void	not_rectang(t_data *data, char *line)
{
	free(line);
	free(data->join);
	get_next_line(data->fd, 1);
	throw_error("it is not rectangular!\n");
}

void	is_line_valid_(t_data *data, int index, int size)
{
	int		i;
	char	*emoji;

	emoji = "10PCEM";
	i = 0;
	if (size != (int)ft_strlen(data->map[index])
		|| data->map[index][0] != '1' || data->map[index][size - 1] != '1')
		clean_and_exit(data->map, "unvalid wall\n");
	while (data->map[index][i + 1])
	{
		if (!ft_strchr(emoji, data->map[index][i]))
			clean_and_exit(data->map, "a character is not in {10PCEM}\n");
		i++;
	}
}

void	check_walls_elemt(t_data *data)
{
	int		i;
	size_t	size;

	size = ft_strlen(data->map[0]);
	is_line_wall_(data->map[0], data);
	i = 1;
	while (data->map[i])
	{
		is_line_valid_(data, i, size);
		i++;
	}
	data->height = i;
	is_line_wall_(data->map[i - 1], data);
}

void	is_player_valid_(t_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P' && check)
				check = false;
			else if (data->map[y][x] == 'P' && !check)
				clean_and_exit(data->map, "player duplicated\n");
			x++;
		}
		y++;
	}
	if (check)
		clean_and_exit(data->map, "No player detected\n");
}

void	is_exit_valid_(t_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'E' && check)
				check = false;
			else if (data->map[y][x] == 'E' && !check)
				clean_and_exit(data->map, "exit duplicated\n");
			x++;
		}
		y++;
	}
	if (check)
		clean_and_exit(data->map, "No exit detected\n");
}

void	is_collectible_valid_(t_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
	data->coins_count = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
			{
				check = false;
				data->coins_count++;
			}
			x++;
		}
		y++;
	}
	if (check)
		clean_and_exit(data->map, "No coins detected\n");
}
void	is_enemy_valid_(t_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
	data->enemy_count = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'M')
			{
				check = false;
				data->enemy_count++;
			}
			x++;
		}
		y++;
	}
	if (check)
		clean_and_exit(data->map, "No enemy detected\n");
}

void	is_line_wall_(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] == '\0' && line [i] == '\n')
			break ;
		if (line[i] != '1')
		{
			clean_up(data->map);
			throw_error("unvalid map : check top and bottom walls\n");
		}
		i++;
	}
}

void	clean_and_exit(char **map, char *err)
{
	clean_up(map);
	throw_error(err);
}

void	check_map_ext_(char *map)
{
	char	*ext;
	int		size;

	size = ft_strlen(map);
	ext = ft_strnstr(map, ".ber", size);
	if (!(ext && ft_strlen(ext) == 4 && size > 4))
		throw_error("unvalid map extension!\n");
}

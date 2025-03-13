/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/13 20:15:59 by hfegrach         ###   ########.fr       */
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
	tmp_map = copy_map_(*data);
	init_player_exit_pos_(data);
	count = data->coins_count + 1;
	if (!check_path_(tmp_map, data->px, data->py, &count))
	{
		clean_up(tmp_map);
		clean_and_exit(data->map, "Unvalid Path\n");
	}
	clean_up(tmp_map);
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

void	open_map_(t_data *data)
{
	check_map_ext_(data->map_name);
	data->fd = open(data->map_name, O_RDONLY);
	if (data->fd < 0)
		throw_error("Can't open the map\n");
}

void	get_map_(t_data *data)
{
	char	*line;
	char	*tmp;

	line = get_next_line(data->fd, 0);
	if (!line)
		throw_error("Unvalid map!\n");
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
		if (line && !(data->width == ft_strlen(line)
				|| data->width - 1 == ft_strlen(line)))
			not_rectang(data, line);
	}
	free(line);
	data->map = ft_split(data->join, '\n');
	data->width--;
	free(data->join);
}

void	check_map_ext_(char *map)
{
	char	*ext;
	int		size;
	char	*filename;

	filename = ft_strrchr(map, '/');
	if (filename)
	{
		filename++;
		size = ft_strlen(filename);
		ext = ft_strrstr(filename, ".ber");
		if (!(ext && ft_strlen(ext) == 4 && size > 4))
			throw_error("Unvalid map name!\n");
	}
	else
	{
		size = ft_strlen(map);
		ext = ft_strrstr(map, ".ber");
		if (!(ext && ft_strlen(ext) == 4 && size > 4))
			throw_error("Unvalid map name!\n");
	}
}

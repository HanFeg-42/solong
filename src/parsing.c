/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/11 01:43:17 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*is_map_valid(char *map, t_solong *var)
{
	t_map_data	data;
	int			fd;

	check_map_ext(map);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		throw_error("Can not open the map\n");
	get_map(fd, &data);
	check_map(&data);
	var->map = copy_map(data);
	var->coins = data.count;
	data.count++;
	init_player_position(&data);
	if (!check_path(data.m, data.x, data.y, &data.count))
		return (clean_up(data.m), "Unvalid Path\n");
	return (clean_up(data.m), NULL);
}

void	get_map(int fd, t_map_data *data)
{
	char	*line;
	char	*join;
	char	*tmp;
	size_t	size;

	line = get_next_line(fd, 0);
	if (!line)
		throw_error("Empty Map!\n");
	size = ft_strlen(line);
	join = ft_strdup("");
	while (line)
	{
		tmp = join;
		join = ft_strjoin(join, line);
		(free(tmp), free(line));
		line = get_next_line(fd, 0);
		if (line && !(size == ft_strlen(line) || size - 1 == ft_strlen(line)))
		{
			(free(line), free(join));
			get_next_line(fd, 1);
			throw_error("Map is not rectangular!\n");
		}
	}
	data->m = ft_split(join, '\n');
	(free(line), free(join));
}

int	check_path(char **map_data, int x, int y, int *count)
{
	if (map_data[y][x] == '1' || !(*count))
		return (false);
	if (map_data[y][x] == 'E' || map_data[y][x] == 'C')
		(*count)--;
	map_data[y][x] = '1';
	check_path(map_data, x - 1, y, count);
	check_path(map_data, x, y - 1, count);
	check_path(map_data, x + 1, y, count);
	check_path(map_data, x, y + 1, count);
	if (*count)
		return (false);
	return (true);
}

void	check_map(t_map_data *data)
{
	is_map_rect(data);
	is_player_valid(data);
	is_collectible_valid(data);
	is_exit_valid(data);
}

void	check_map_ext(char *map)
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

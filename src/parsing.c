/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 23:26:01 by hfegrach         ###   ########.fr       */
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
		throw_error("failed to open");
	get_map(fd, &data);
	check_map(&data);
	var->map = copy_map(data);
	var->coins = data.count;
	data.count++;
	init_player_position(&data);
	if (!check_path(data.m, data.x, data.y, &data.count))
		return (clean_up(data.m), "unvalid path\n");
	return (clean_up(data.m), NULL);
}

void	get_map(int fd, t_map_data *data)
{
	char	*line;
	char	*join;
	char	*tmp;
	size_t	size;

	line = get_next_line(fd, 0);
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
			throw_error("it is not rectangular!\n");
		}
	}
	free(line);
	data->m = ft_split(join, '\n');
	free(join);
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

	size = ft_strlen(map);
	ext = ft_strnstr(map, ".ber", size);
	if (!(ext && ft_strlen(ext) == 4 && size > 4))
		throw_error("unvalid map extension!\n");
}

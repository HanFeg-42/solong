/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:44:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 21:20:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	is_line_valid(char *line, int size)
{
	int		i;
	char	*emoji;

	emoji = "10PCE";
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

void	is_map_rect(t_map_data *data)
{
	int		i;
	size_t	size;

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

void	is_player_valid(t_map_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
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

void	is_exit_valid(t_map_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
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

void	is_collectible_valid(t_map_data *data)
{
	int	x;
	int	y;
	int	check;
	int	count;

	check = true;
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

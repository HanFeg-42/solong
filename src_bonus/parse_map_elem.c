/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:26:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 23:20:18 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

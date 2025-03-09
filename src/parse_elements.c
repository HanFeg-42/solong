/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:44:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/06 13:28:04 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	is_line_valid(t_map_data *data, int index, int size)
{
	int		i;
	char	*emoji;

	emoji = "10PCE";
	i = 0;
	if (size != (int)ft_strlen(data->m[index])
		|| data->m[index][0] != '1' || data->m[index][size - 1] != '1')
	{
		clean_up(data->m);
		throw_error("Unvalid Wall\n");
	}
	while (data->m[index][i + 1])
	{
		if (!ft_strchr(emoji, data->m[index][i]))
		{
			clean_up(data->m);
			throw_error("Unvalid element in the map\n");
		}
		i++;
	}
}

void	is_map_rect(t_map_data *data)
{
	int		i;
	size_t	size;

	size = ft_strlen(data->m[0]);
	is_line_wall(data->m[0], data);
	i = 1;
	while (data->m[i])
	{
		is_line_valid(data, i, size);
		i++;
	}
	data->height = i;
	is_line_wall(data->m[i - 1], data);
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
			{
				clean_up(data->m);
				throw_error("Player duplicated\n");
			}
			x++;
		}
		y++;
	}
	if (check)
		(clean_up(data->m), throw_error("No player detected\n"));
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
			{
				clean_up(data->m);
				throw_error("Exit duplicated\n");
			}
			x++;
		}
		y++;
	}
	if (check)
		(clean_up(data->m), throw_error("No exit detected\n"));
}

void	is_collectible_valid(t_map_data *data)
{
	int	x;
	int	y;
	int	check;

	check = true;
	data->count = 0;
	y = 0;
	while (data->m[y])
	{
		x = 0;
		while (data->m[y][x])
		{
			if (data->m[y][x] == 'C')
			{
				check = false;
				data->count++;
			}
			x++;
		}
		y++;
	}
	if (check)
		(clean_up(data->m), throw_error("No coin detected\n"));
}

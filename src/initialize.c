/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:08:58 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 22:09:50 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_map_width(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

void	init_player_exit_position(t_mlx_data *data)
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

void	initialize_data(t_mlx_data *data)
{
	data->coins = 0;
	data->count = 0;
	data->old_count = 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
	data->ex = 0;
	data->ey = 0;
	data->px = 0;
	data->px = 0;
}

void	display_moves_nbr(t_mlx_data *data)
{
	char *str =NULL;
int i =0;
	while (i < data->width)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,data->images[1], i *64, data->height*64);
		i++;
	}
	if (data->old_count != data->count)
	{
		ft_printf("Number of moves: %d\n", data->count);
		data->old_count = data->count;
	}
	str = ft_itoa(data->count);
	mlx_set_font(data->mlx_ptr, data->mlx_win, "9x15");
	mlx_string_put(data->mlx_ptr, data->mlx_win,12, data->height*64 + 32, 0x000000, "Number of moves :");
	mlx_string_put(data->mlx_ptr, data->mlx_win,64*3 -20, data->height*64 + 32, 0x000000, str);
	free(str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:54:11 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 22:41:12 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ren_wall(t_mlx_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->images[0], SCALE * x, SCALE * y);
}

void	ren_floor(t_mlx_data *data, int x, int y)
{
	if (data->map[y][x] == '0'
		&& !(x == data->ex && y == data->ey && !data->coins))
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->images[1], SCALE * x, SCALE * y);
}

void	ren_exit(t_mlx_data *data, int x, int y)
{
	if (x == data->ex && y == data->ey)
	{
		if (data->coins)
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->images[1], SCALE * x, SCALE * y);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->images[3], SCALE * x, SCALE * y);
	}
}

void	ren_player(t_mlx_data *data, int x, int y)
{
	if (data->map[y][x] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->images[2], SCALE * x, SCALE * y);
}

void	ren_coin(t_mlx_data *data, int x, int y)
{
	if (data->map[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->images[4], SCALE * x, SCALE * y);
}

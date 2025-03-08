/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:32:37 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/08 00:09:38 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ren_enemy_(t_data *data, int x, int y)
{
	static int	fire_index;

	if (fire_index == 5)
		fire_index = 0;
	if (data->map[y][x] == 'M')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->enemy[fire_index], SCALE * x, SCALE * y);
	fire_index++;
}

void	ren_floor_(t_data *data, int x, int y)
{
	if (data->map[y][x] == '0'
		&& !(x == data->ex && y == data->ey && !data->coins_count))
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->floor, SCALE * x, SCALE * y);
}

void	ren_exit_(t_data *data, int x, int y)
{
	if (x == data->ex && y == data->ey)
	{
		if (data->coins_count)
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->floor, SCALE * x, SCALE * y);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
				data->exit, SCALE * x, SCALE * y);
	}
}

void	ren_player_(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->player, SCALE * x, SCALE * y);
}

void	ren_coin_(t_data *data, int x, int y)
{
	static int	img_indx;
	static int	dellay;

		if (img_indx == 5)
			img_indx = 0;
	if (data->map[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->coin[img_indx], SCALE * x, SCALE * y);
	if (++dellay %10000 == 0)
	{
		img_indx++;
	}
}

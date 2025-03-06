/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:40:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/06 16:40:36 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	rendering_(t_data *data)
{
	render_images_(data);
	display_moves_nbr(data);
	return (0);
}
void	render_images_(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			ren_wall_(data, x, y);
			ren_exit_(data, x, y);
			ren_floor_(data, x, y);
			ren_player_(data, x, y);
			ren_coin_(data, x, y);
			x++;
		}
		y++;
	}
}
void	ren_wall_(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->wall, SCALE * x, SCALE * y);
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
	static int img_indx;
	static int dellay;

	if (++dellay % 100 == 0)
	{
		if (img_indx == 5)
			img_indx = 0;
	}
	if (data->map[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->coin[img_indx], SCALE * x, SCALE * y);
	img_indx++;
}
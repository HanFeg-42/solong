/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:40:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 04:21:44 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	rendering_(t_data *data)
{
	render_images_(data);
	display_moves_nbr_(data);
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
			ren_enemy_(data, x, y);
			ren_coin_(data, x, y);
			x++;
		}
		y++;
	}
}
void	display_moves_nbr_(t_data *data)
{
	char	*str = NULL;
	size_t	i = 0;
	while (i < data->width)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,data->floor, i * 64, data->height * 64);
		i++;
	}
	if (data->old_moves_count != data->moves_count)
	{
		// ft_printf("Number of moves: %d\n", data->moves_count);
		data->old_moves_count = data->moves_count;
	}
	str = ft_itoa(data->moves_count);
	mlx_set_font(data->mlx_ptr, data->mlx_win, "9x15");
	mlx_string_put(data->mlx_ptr, data->mlx_win,12, data->height*64 + 32, 0x000000, "Number of moves :");
	mlx_string_put(data->mlx_ptr, data->mlx_win,64*3 -20, data->height*64 + 32, 0x000000, str);
	free(str);
}

void	ren_wall_(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->wall, SCALE * x, SCALE * y);
}
void	ren_enemy_(t_data *data, int x, int y)
{
	static int fire_index;

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
	static int img_indx;
	int i;

	if (img_indx == 5)
		img_indx = 0;
	if (data->map[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->coin[img_indx], SCALE * x, SCALE * y);
	img_indx++;
	i = 0;
	while (i < 99999)
	    i++;
}
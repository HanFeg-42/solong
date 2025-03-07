/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:40:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 17:32:30 by hfegrach         ###   ########.fr       */
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
	// int i;

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
			// i = 0;
			// while (i < RANDOM)
			// 	i++;
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
		data->old_moves_count = data->moves_count;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:40:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/09 18:01:20 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	rendering_(t_data *data)
{
	static int	dellay;

	if (++dellay % 100 == 0)
		move_enemy(data);
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
	char	*str;
	size_t	i;

	str = NULL;
	i = 0;
	if (data->old_moves_count != data->moves_count)
	{
		while (i < data->width)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->floor,
				i * SCALE, data->height * SCALE);
			i++;
		}
		data->old_moves_count = data->moves_count;
		str = ft_itoa(data->moves_count);
		mlx_set_font(data->mlx_ptr, data->mlx_win, "9x15");
		mlx_string_put(data->mlx_ptr, data->mlx_win, 12,
			data->height * SCALE + 32, 0x000000, "Number of moves :");
		mlx_string_put(data->mlx_ptr, data->mlx_win, SCALE * 3 - 20,
			data->height * SCALE + 32, 0x000000, str);
		free(str);
	}
}

void	ren_wall_(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
			data->wall, SCALE * x, SCALE * y);
}

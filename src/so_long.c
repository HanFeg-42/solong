/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 01:32:37 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	so_long(t_mlx_data *data)
{
	int (h), (w);
	h = get_map_height(data->map);
	w = get_map_width(data->map);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(1);
	data->mlx_win = mlx_new_window(data->mlx_ptr, w * SCALE,
			h * SCALE, "so_long");
	if (!data->mlx_win)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	loading_images(data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_hook(data->mlx_win, 2, (1L << 0), key_press, data);
	mlx_loop_hook(data->mlx_ptr, rendering_to_win, data);
	mlx_loop(data->mlx_ptr);
}

void	loading_images(t_mlx_data *data)
{
	int (w), (h);
	data->images[0] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_WALL, &w, &h);
	data->images[1] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_FLOOR, &w, &h);
	data->images[2] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_PLAYER, &w, &h);
	data->images[3] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_EXIT, &w, &h);
	data->images[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			PATH_COLLECTIBLE, &w, &h);
}

int	rendering_to_win(t_mlx_data *data)
{
	render_images(data);
	display_moves_nbr(data);
	return (0);
}

void	render_images(t_mlx_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			ren_wall(data, x, y);
			ren_exit(data, x, y);
			ren_floor(data, x, y);
			ren_player(data, x, y);
			ren_coin(data, x, y);
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_solong	var;
	t_mlx_data	data;

	if (ac != 2)
		throw_error("unvalid argument!\n");
	var.err = is_map_valid(av[1], &var);
	if (var.err)
		throw_error(var.err);
	printf("\033[32m map is valid congrats! \033[0m\n");
	initialize_data(&data);
	data.map = var.map;
	data.coins = var.coins;
	init_player_exit_position(&data);
	so_long(&data);
	clean_up(var.map);
	return (0);
}

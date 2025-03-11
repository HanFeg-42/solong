/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/11 01:47:13 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//.ber.ber
// dossier : .ber
// map khawya
//  valgrind ./so_long a.ber + map khawya
// protect imgs
//  so_long/so_long so_long/maps/map1.ber

void	so_long(t_mlx_data *data)
{
	data->height = get_map_height(data->map);
	data->width = get_map_width(data->map);
	if (data->width > MAX_WIDTH || data->height > MAX_HEIGHT)
		(clean_up(data->map), throw_error("Unvalid map size!\n"));
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit(1);
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->width * SCALE,
			data->height * SCALE, "so_long");
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
	int (w), (h), (i);
	data->images[0] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_WALL, &w, &h);
	data->images[1] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_FLOOR, &w, &h);
	data->images[2] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_PLAYER, &w, &h);
	data->images[3] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_EXIT, &w, &h);
	data->images[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			PATH_COLLECTIBLE, &w, &h);
	if (!data->images[0] || !data->images[1] || !data->images[2]
		|| !data->images[3] || !data->images[4])
	{
		ft_printf("Can't load images!\n");
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		clean_up(data->map);
		i = 0;
		while (i < 5)
		{
			if (data->images[i])
				mlx_destroy_image(data->mlx_ptr, data->images[i]);
			i++;
		}
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
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
		throw_error("Unvalid Arguments!\n");
	var.err = is_map_valid(av[1], &var);
	if (var.err)
		throw_error(var.err);
	ft_printf("\033[36m--Game Started-- \033[0m\n");
	initialize_data(&data);
	data.map = var.map;
	data.coins = var.coins;
	init_player_exit_position(&data);
	so_long(&data);
	clean_up(var.map);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/27 15:32:28 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int close_window(t_mlx_data *data)
{
    printf("you clicked red cross\n");
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (1);
}
int    key_press(int key, t_mlx_data *data)
{
    if (key == XK_Escape)
    {
        printf("you pressed ESC\n");
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(0);
    }
	// else if (key == XK_W || key == ARROW_U)
	// 	move_player("up", data->map);
	// else if (key == XK_S || key == ARROW_D)
	// 	move_player("down", data->map);
	// else if (key == XK_D || key == ARROW_R)
	// 	move_player("right", data->map);
	// else if (key == XK_A || key == ARROW_L)
	// 	move_player("left", data->map);
    return (0);
}
// void move_player(char *move, t_map *map_data)
// {
// 	if (is_move_valid(move, map_data))
// 	{
// 		if (ft_strncmp(move, "up"))
			// data->map>[]
// 	}
// }

int	get_map_height(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
int	get_map_width(char **map)
{
	int i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

void	so_long(t_mlx_data *data)
{
	int h = get_map_height(data->map);
	int w = get_map_width(data->map);
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
	rendering_to_win(data);
	mlx_hook(data->mlx_win, 17, 0, close_window, &data);
    mlx_key_hook(data->mlx_win, key_press, &data);
	// mlx_loop_hook(data->mlx_ptr, );
	mlx_loop(data->mlx_ptr);
}

void	loading_images(t_mlx_data *data)
{
	int w, h;

	data->images[0] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_WALL, &w, &h);
	data->images[1] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_FLOOR, &w, &h);
	data->images[2] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_PLAYER, &w, &h);
	data->images[3] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_EXIT, &w, &h);
	data->images[4] = mlx_xpm_file_to_image(data->mlx_ptr, PATH_COLLECTIBLE, &w, &h);
	if (!data->images[0] || !data->images[1] || !data->images[2] || !data->images[3] || !data->images[4])
	{
		printf("Error\n");
		exit(1);
	}
}

void	rendering_to_win(t_mlx_data *data)
{
	int x;
	int y;
	int tile_size;

	tile_size = SCALE;
	y = 0;
	while(data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[0], tile_size * x, tile_size * y);
			if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[1], tile_size * x, tile_size * y);
			if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[2], tile_size * x, tile_size * y);
			if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[3], tile_size * x, tile_size * y);
			if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[4], tile_size * x, tile_size * y);
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	t_solong    var;
	t_mlx_data data;

	if (ac != 2)
		throw_error("unvalid argument!\n");
	if ((var.err = is_map_valid(av[1], &var)))
		throw_error(var.err);
	printf("\033[32m map is valid congrats! \033[0m\n");
	// var.map[3][6] = 'B';
	print_map(var.map);\
	data.map = var.map;
	so_long(&data);
	clean_up(var.map);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/25 01:04:12 by hfegrach         ###   ########.fr       */
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
    return (0);
}

void	so_long(char **map)
{
	t_mlx_data data;

	init_map_data(&data, map);
	// data.map->m = copy_map_(map);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit(1);
	data.mlx_win = mlx_new_window(data.mlx_ptr, data.map->width * SCALE,
					data.map->height * SCALE, "so_long");
	if (!data.mlx_win)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		exit(1);
	} 
	loading_images(&data);
	rendering_to_win(&data);
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
    mlx_key_hook(data.mlx_win, key_press, &data);
	mlx_loop(data.mlx_ptr);
}

char **copy_map_(char **map)
{
	char	**ret;
	int		i;
	int index;
	int height;

	index = 0;
	while(map[index])
		index++;
	height = index;
	map = map;
	ret = malloc(sizeof(char *) * (height + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (map[i])
	{
		ret[i] = ft_strdup(map[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	init_map_data(t_mlx_data *data, char **map)
{
	// char	**ret;
	int		i;
	int index;
	int height;

	index = 0;
	while(map[index])
		index++;
	height = index;
	map = map;
	data->map->m = malloc(sizeof(char *) * (height + 1));
	// if (!ret)
	// 	return (NULL);
	i = 0;
	while (map[i])
	{
		data->map->m[i] = ft_strdup(map[i]);
		i++;
	}
	data->map->m[i] = NULL;
}

void	loading_images(t_mlx_data *data)
{
	data->images[0] = mlx_xpm_file_to_image(data->mlx_ptr,
				PATH_WALL, &data->map->width, &data->map->height);
	data->images[1] = mlx_xpm_file_to_image(data->mlx_ptr,
				PATH_FLOOR, &data->map->width, &data->map->height);
	data->images[2] = mlx_xpm_file_to_image(data->mlx_ptr,
				PATH_PLAYER, &data->map->width, &data->map->height);
	data->images[3] = mlx_xpm_file_to_image(data->mlx_ptr,
				PATH_EXIT, &data->map->width, &data->map->height);
	data->images[4] = mlx_xpm_file_to_image(data->mlx_ptr,
				PATH_COLLECTIBLE, &data->map->width, &data->map->height);
}

void	rendering_to_win(t_mlx_data *data)
{
	int x;
	int y;
	int tile_size;

	tile_size = SCALE;
	y = 0;
	while(data->map->m[y])
	{
		x = 0;
		while (data->map->m[y][x])
		{
			if (data->map->m[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[0], tile_size * x, tile_size * y);
			if (data->map->m[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[1], tile_size * x, tile_size * y);
			if (data->map->m[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[2], tile_size * x, tile_size * y);
			if (data->map->m[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[3], tile_size * x, tile_size * y);
			if (data->map->m[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[4], tile_size * x, tile_size * y);
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	t_solong    var;

	if (ac != 2)
		throw_error("unvalid argument!\n");
	if ((var.err = is_map_valid(av[1], &var)))
		throw_error(var.err);
	printf("\033[32m map is valid congrats! \033[0m\n");
	print_map(var.map);
	clean_up(var.map);
	so_long(var.map);
	return (0);
}
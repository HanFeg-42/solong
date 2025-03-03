/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/03 00:39:45 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int close_window(t_mlx_data *data)
{
    printf("you clicked red cross\n");
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
	clean_up(data->map);
    exit(0);
    return (1);
}
int    key_press(int key, t_mlx_data *data)
{
	// int i;

    if (key == XK_Escape)
    {
        printf("you pressed ESC\n");
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
        mlx_destroy_display(data->mlx_ptr);
		clean_up(data->map);
		// i = 0;
		// while (data->images[i])
		// 	mlx_destroy_image(data->mlx_ptr, data->images[i++]);
        free(data->mlx_ptr);
        exit(0);
    }
	else if (key == XK_w || key == ARROW_U)
		move_player("up", data);
	else if (key == XK_s || key == ARROW_D)
		move_player("down", data);
	else if (key == XK_d || key == ARROW_R)
		move_player("right", data);
	else if (key == XK_a || key == ARROW_L)
		move_player("left", data);
    return (0);
}
void move_player(char *move, t_mlx_data *data)
{
	if (is_move_valid(move, data))
	{
		printf("player pos: x=%d---y=%d\n",data->px, data->py);
		if (!ft_strncmp(move, "up", 2))
		{
			check_exit(move, data);
			// {
			data->map[data->py][data->px] = '0';
			if (data->map[data->py - 1][data->px] == 'C')
				data->coins--;
			data->map[data->py - 1][data->px] = 'P';
			data->py--;
			// }
			// else
			// {
			// 	data->map[data->py][data->px] = '0';
			// 	data->map[data->py - 1][data->px] = 'X';
			// 	data->py--;
			// }
		}
		else if (!ft_strncmp(move, "down", 4))
		{
			check_exit(move, data);
			data->map[data->py][data->px] = '0';
			if (data->map[data->py + 1][data->px] == 'C')
			{
				data->coins--;
			}
			data->map[data->py + 1][data->px] = 'P';
			data->py++;
		}
		else if (!ft_strncmp(move, "right", 4))
		{
			check_exit(move, data);
			data->map[data->py][data->px] = '0';
			if (data->map[data->py][data->px + 1] == 'C')
				data->coins--;
			data->map[data->py][data->px + 1] = 'P';
			data->px++;
		}
		else if (!ft_strncmp(move, "left", 4))
		{
			check_exit(move, data);
			data->map[data->py][data->px] = '0';
			if (data->map[data->py][data->px - 1] == 'C')
				data->coins--;
			data->map[data->py][data->px - 1] = 'P';
			data->px--;
		}
	}
}

int	check_exit(char *move, t_mlx_data *data)
{
	if (!ft_strncmp(move, "up", 2) && data->map[data->py - 1][data->px] != 'E' && !(data->px == data->ex && data->py - 1 == data->ey && !data->coins))
		return 0;
	else if (!ft_strncmp(move, "down", 4) && data->map[data->py + 1][data->px] != 'E' && !(data->px == data->ex && data->py + 1 == data->ey && !data->coins))
		return 0;
	else if (!ft_strncmp(move, "right", 4) && data->map[data->py][data->px + 1] != 'E' && !(data->px + 1 == data->ex && data->py == data->ey && !data->coins))
		return 0;
	else if (!ft_strncmp(move, "left", 4) && data->map[data->py][data->px - 1] != 'E' && !(data->px - 1 == data->ex && data->py == data->ey && !data->coins))
		return 0;
	printf("%d\n", data->coins);
	if (data->coins == 0)
	{
		printf("you WIN\n");
		data->map[data->py][data->px] = '0';
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		clean_up(data->map);
		exit(1);
	}
	else
	{
		return 1;
	}
}

int is_move_valid(char *move, t_mlx_data *data)
{
	if (!ft_strncmp(move, "up", 2) && data->map[data->py - 1][data->px] == '1')
		return (0);
	else if (!ft_strncmp(move, "down", 4) && data->map[data->py + 1][data->px] == '1')
		return (0);
	else if (!ft_strncmp(move, "right", 4) && data->map[data->py][data->px + 1] =='1')
		return (0);
	else if (!ft_strncmp(move, "left", 4) && data->map[data->py][data->px - 1] == '1')
		return (0);
	return 1;
}

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
	// rendering_to_win(data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
    mlx_hook(data->mlx_win,2 , (1L<<0), key_press, data);
	mlx_loop_hook(data->mlx_ptr, rendering_to_win, data);
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
	data->images[5] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/p_at_exit.xpm", &w, &h);
	if (!data->images[0] || !data->images[1] || !data->images[2] || !data->images[3] || !data->images[4])
	{
		printf("Error\n");
		exit(1);
	}
}

int	rendering_to_win(t_mlx_data *data)
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
			else if (data->map[y][x] == '0' && !(x == data->ex && y == data->ey && !data->coins))
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[1], tile_size * x, tile_size * y);
			else if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[2], tile_size * x, tile_size * y);
			else if (x == data->ex && y == data->ey && !data->coins)
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[3], tile_size * x, tile_size * y);
			else if (x == data->ex && y == data->ey && data->coins)
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[1], tile_size * x, tile_size * y);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[4], tile_size * x, tile_size * y);
			if (data->map[y][x] == 'X')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->images[5], tile_size * x, tile_size * y);
			x++;
		}
		y++;
	}
	return (0);
}

void init_player_exit_position(t_mlx_data *data)
{
	int (x), (y);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->px = x;
				data->py = y;
			}
			if (data->map[y][x] == 'E')
			{
				data->ex = x;
				data->ey = y;
			}
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
// exit(1);
	t_solong    var;
	t_mlx_data data;
printf("hello\n");
	if (ac != 2)
		throw_error("unvalid argument!\n");
	if ((var.err = is_map_valid(av[1], &var)))
		throw_error(var.err);
	printf("\033[32m map is valid congrats! \033[0m\n");
	print_map(var.map);
	data.map = var.map;
	data.coins = var.coins;
	printf("%d\n\n\n\n\n", data.coins);
	init_player_exit_position(&data);
	so_long(&data);
	clean_up(var.map);
	return (0);
}

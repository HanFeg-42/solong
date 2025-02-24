/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/24 13:35:40 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

#define SCALE 50

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
	t_map_data m_data;

	init_map_data(&m_data, map);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit(1);
	data.mlx_win = mlx_new_window(data.mlx_ptr, m_data.width * SCALE,
					m_data.height * SCALE, "so_long");
	if (!data.mlx_win)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		exit(1);
	}
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
    mlx_key_hook(data.mlx_win, key_press, &data);
	mlx_loop(data.mlx_ptr);
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
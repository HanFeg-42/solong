/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:26:12 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 02:38:04 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (ft_putstr_fd("Unvalid arguments!", 2), 1);
	init0_data(av[1], &data);
	is_map_valid_(&data);
	printf("\033[32m map is valid congrats! \033[0m\n");
	so_long_(&data);
	clean_up(data.map);
	return (0);
}

void	so_long_(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->width * SCALE,
			data->height * SCALE + 64, "so_long");
	loading_images_(data);
	mlx_hook(data->mlx_win, 17, 0, close_window_, data);
	mlx_hook(data->mlx_win, 2, (1L << 0), key_press_, data);
	mlx_loop_hook(data->mlx_ptr, rendering_, data);
	mlx_loop(data->mlx_ptr);
}

void	loading_images_(t_data *data)
{
	int (w), (h);
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, "textures/playerG.xpm", &w, &h);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "textures/wallG.xpm", &w, &h);
	data->floor = mlx_xpm_file_to_image(data->mlx_ptr, "textures/green0.xpm", &w, &h);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "textures/exitG.xpm", &w, &h);
	data->coin[0] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/coin/9.xpm", &w, &h);
	data->coin[1] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/coin/10.xpm", &w, &h);
	data->coin[2] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/coin/11.xpm", &w, &h);
	data->coin[3] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/coin/12.xpm", &w, &h);
	data->coin[4] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/coin/13.xpm", &w, &h);
	data->enemy[0] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/fire/1.xpm", &w, &h);
	data->enemy[1] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/fire/2.xpm", &w, &h);
	data->enemy[2] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/fire/3.xpm", &w, &h);
	data->enemy[3] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/fire/4.xpm", &w, &h);
	data->enemy[4] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/fire/5.xpm", &w, &h);
}



void	init0_data(char *arg, t_data *data)
{
	data->map_name = arg;
	data->height = 0;
	data->old_moves_count = 0;
	data->moves_count = 0;
}


//TODO : 1 - bonus parsing -----------------------> DONE
//TODO : 2 - render the game
//TODO : 3 - display moves on window
//TODO : 4 - coin animation
//TODO : 5 - handle enemy behavior

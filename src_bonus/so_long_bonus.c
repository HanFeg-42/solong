/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:26:12 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/11 03:11:57 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
/* TO DO */
//.ber.ber ======================================> done
// dossier : .ber ===============================> done
// map khawya ===================================> done
//  valgrind ./so_long a.ber + map khawya =======> done
// protect imgs =================================> done
//  so_long/so_long so_long/maps/map1.ber =======> done
// get_next_line --TIMEOUT--

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Unvalid Arguments!\n", 2), 1);
	init0_data(av[1], &data);
	is_map_valid_(&data);
	ft_printf("\033[36m--Game Started-- \033[0m\n");
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
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, P_PATH, &w, &h);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, W_PATH, &w, &h);
	data->floor = mlx_xpm_file_to_image(data->mlx_ptr, F_PATH, &w, &h);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, E_PATH, &w, &h);
	data->coin[0] = mlx_xpm_file_to_image(data->mlx_ptr, C1_PATH, &w, &h);
	data->coin[1] = mlx_xpm_file_to_image(data->mlx_ptr, C2_PATH, &w, &h);
	data->coin[2] = mlx_xpm_file_to_image(data->mlx_ptr, C3_PATH, &w, &h);
	data->coin[3] = mlx_xpm_file_to_image(data->mlx_ptr, C4_PATH, &w, &h);
	data->coin[4] = mlx_xpm_file_to_image(data->mlx_ptr, C5_PATH, &w, &h);
	data->enemy[0] = mlx_xpm_file_to_image(data->mlx_ptr, M1_PATH, &w, &h);
	data->enemy[1] = mlx_xpm_file_to_image(data->mlx_ptr, M2_PATH, &w, &h);
	data->enemy[2] = mlx_xpm_file_to_image(data->mlx_ptr, M3_PATH, &w, &h);
	data->enemy[3] = mlx_xpm_file_to_image(data->mlx_ptr, M4_PATH, &w, &h);
	data->enemy[4] = mlx_xpm_file_to_image(data->mlx_ptr, M5_PATH, &w, &h);
	protect_images_(data);
}

void	protect_images_(t_data *data)
{
	if (!data->player || !data->wall || !data->floor || !data->exit
		|| !data->coin[0] || !data->coin[1] || !data->coin[2] || !data->coin[3]
		|| !data->coin[4] || !data->enemy[0] || !data->enemy[1]
		|| !data->enemy[2] || !data->enemy[3] || !data->enemy[4])
	{
		ft_printf("Can't load images!\n");
		exit_game(data);
	}
}

void	init0_data(char *arg, t_data *data)
{
	data->map_name = arg;
	data->height = 0;
	data->old_moves_count = 1;
	data->moves_count = 0;
}

//TODO : 1 - bonus parsing -----------------------> DONE
//TODO : 2 - render the game ---------------------> DONE
//TODO : 3 - display moves on window -------------> DONE
//TODO : 4 - coin animation ----------------------> DONE
//TODO : 5 - handle enemy behavior ---------------> DONE

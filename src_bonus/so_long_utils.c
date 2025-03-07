/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 03:55:58 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	close_window_(t_data *data)
{
	ft_printf("you clicked red cross\n");
	exit_game(data);
	return (1);
}
void	exit_game(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	clean_up(data->map);
	destroy_images(data);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	destroy_images(t_data *data)
{
	int	i;

	mlx_destroy_image(data->mlx_ptr, data->player);
	mlx_destroy_image(data->mlx_ptr, data->exit);
	mlx_destroy_image(data->mlx_ptr, data->floor);
	mlx_destroy_image(data->mlx_ptr, data->wall);
	i = 0;
	while (i < 5)
		mlx_destroy_image(data->mlx_ptr, data->coin[i++]);
	i = 0;
	while (i < 5)
		mlx_destroy_image(data->mlx_ptr, data->enemy[i++]);
}

int	key_press_(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		ft_printf("you pressed ESC\n");
		exit_game(data);
	}
	else if (key == XK_w || key == ARROW_U)
		move_player_("up", data);
	else if (key == XK_s || key == ARROW_D)
		move_player_("down", data);
	else if (key == XK_d || key == ARROW_R)
		move_player_("right", data);
	else if (key == XK_a || key == ARROW_L)
		move_player_("left", data);
	return (0);
}

int	check_exit_(int y, int x, t_data *data) // le logique doit changer !!!!!!!!!!!!!!!!!!
{
	// if (!ft_strncmp(move, "up", 2) && data->map[data->py - 1][data->px] != 'E' && data->map[data->py - 1][data->px] != 'M'
	// 	&& !(data->px == data->ex && data->py - 1 == data->ey && !data->coins_count))
	// 	return (0);
	// else if (!ft_strncmp(move, "down", 4)
	// 	&& data->map[data->py + 1][data->px] != 'E' && data->map[data->py + 1][data->px] != 'M'
	// 	&& !(data->px == data->ex && data->py + 1 == data->ey && !data->coins_count))
	// 	return (0);
	// else if (!ft_strncmp(move, "right", 4)
	// 	&& data->map[data->py][data->px + 1] != 'E' && data->map[data->py][data->px + 1] != 'M'
	// 	&& !(data->px + 1 == data->ex && data->py == data->ey && !data->coins_count))
	// 	return (0);
	// else if (!ft_strncmp(move, "left", 4)
	// 	&& data->map[data->py][data->px - 1] != 'E' && data->map[data->py][data->px - 1] != 'M'
	// 	&& !(data->px - 1 == data->ex && data->py == data->ey && !data->coins_count))
	// 	return (0);
	if (data->map[y][x] != 'E' && data->map[y][x] != 'M' && !(data->ex == x && data->ey == y && !data->coins_count))
        return (0);
	if (data->ex == x && data->ey == y && !data->coins_count)
	{
		ft_printf("you WIN\n");
		exit_game(data);
	}
	else if (data->map[y][x] == 'M')
	{
		ft_printf("you LOST\n");
		exit_game(data);
	}
	return (1);
}


int	is_move_valid_(char *move, t_data *data)
{
	if (!ft_strncmp(move, "up", 2) && data->map[data->py - 1][data->px] == '1')
		return (0);
	else if (!ft_strncmp(move, "down", 4)
		&& data->map[data->py + 1][data->px] == '1')
		return (0);
	else if (!ft_strncmp(move, "right", 4)
		&& data->map[data->py][data->px + 1] == '1')
		return (0);
	else if (!ft_strncmp(move, "left", 4)
		&& data->map[data->py][data->px - 1] == '1')
		return (0);
	return (1);
}

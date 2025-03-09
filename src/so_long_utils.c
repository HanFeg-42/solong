/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 14:12:09 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	close_window(t_mlx_data *data)
{
	int	i;

	ft_printf("you clicked Red Cross\n");
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	clean_up(data->map);
	i = 0;
	while (i < 5)
		mlx_destroy_image(data->mlx_ptr, data->images[i++]);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (1);
}

int	key_press(int key, t_mlx_data *data)
{
	int	i;

	if (key == XK_Escape)
	{
		ft_printf("you pressed ESC\n");
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		clean_up(data->map);
		i = 0;
		while (i < 5)
			mlx_destroy_image(data->mlx_ptr, data->images[i++]);
		mlx_destroy_display(data->mlx_ptr);
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

void	game_over(t_mlx_data *data)
{
	int	i;

	ft_printf("\033[32mCongratulations! You WON the Game\033[0m\n");
	data->map[data->py][data->px] = '0';
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	i = 0;
	while (i < 5)
		mlx_destroy_image(data->mlx_ptr, data->images[i++]);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	clean_up(data->map);
	exit(0);
}

int	check_exit(char *move, t_mlx_data *data)
{
	if (!ft_strncmp(move, "up", 2) && data->map[data->py - 1][data->px] != 'E'
		&& !(data->px == data->ex && data->py - 1 == data->ey && !data->coins))
		return (0);
	else if (!ft_strncmp(move, "down", 4)
		&& data->map[data->py + 1][data->px] != 'E'
		&& !(data->px == data->ex && data->py + 1 == data->ey && !data->coins))
		return (0);
	else if (!ft_strncmp(move, "right", 4)
		&& data->map[data->py][data->px + 1] != 'E'
		&& !(data->px + 1 == data->ex && data->py == data->ey && !data->coins))
		return (0);
	else if (!ft_strncmp(move, "left", 4)
		&& data->map[data->py][data->px - 1] != 'E'
		&& !(data->px - 1 == data->ex && data->py == data->ey && !data->coins))
		return (0);
	if (!data->coins)
		game_over(data);
	return (1);
}

int	is_move_valid(char *move, t_mlx_data *data)
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

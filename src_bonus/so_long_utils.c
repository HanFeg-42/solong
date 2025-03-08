/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 23:29:35 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

int	check_exit_(int y, int x, t_data *data)
{
	if (data->map[y][x] != 'E' && data->map[y][x] != 'M'
		&& !(data->ex == x && data->ey == y && !data->coins_count))
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

int	close_window_(t_data *data)
{
	ft_printf("you clicked red cross\n");
	exit_game(data);
	return (1);
}

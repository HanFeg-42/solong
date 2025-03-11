/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:44:47 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/11 03:12:48 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move_player(char *move, t_mlx_data *data)
{
	data->old_count = data->count;
	++data->count;
	if (is_move_valid(move, data))
	{
		if (!ft_strncmp(move, "up", 2))
		{
			check_exit(move, data);
			up(data);
		}
		else if (!ft_strncmp(move, "down", 4))
		{
			check_exit(move, data);
			down(data);
		}
		else if (!ft_strncmp(move, "right", 4))
		{
			check_exit(move, data);
			right(data);
		}
		else if (!ft_strncmp(move, "left", 4))
		{
			check_exit(move, data);
			left(data);
		}
	}
}

void	up(t_mlx_data *data)
{
	data->map[data->py][data->px] = '0';
	if (data->map[data->py - 1][data->px] == 'C')
		data->coins--;
	data->map[data->py - 1][data->px] = 'P';
	data->py--;
}

void	down(t_mlx_data *data)
{
	data->map[data->py][data->px] = '0';
	if (data->map[data->py + 1][data->px] == 'C')
		data->coins--;
	data->map[data->py + 1][data->px] = 'P';
	data->py++;
}

void	right(t_mlx_data *data)
{
	data->map[data->py][data->px] = '0';
	if (data->map[data->py][data->px + 1] == 'C')
		data->coins--;
	data->map[data->py][data->px + 1] = 'P';
	data->px++;
}

void	left(t_mlx_data *data)
{
	data->map[data->py][data->px] = '0';
	if (data->map[data->py][data->px - 1] == 'C')
		data->coins--;
	data->map[data->py][data->px - 1] = 'P';
	data->px--;
}

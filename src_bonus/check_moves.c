/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:44:47 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/09 02:58:39 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move_player_(char *move, t_data *data)
{
	if (is_move_valid_(move, data))
	{
		data->old_moves_count = data->moves_count;
		++data->moves_count;
		if (!ft_strncmp(move, "up", 2))
		{
			check_exit_(data->py - 1, data->px, data);
			up_(data);
		}
		else if (!ft_strncmp(move, "down", 4))
		{
			check_exit_(data->py + 1, data->px, data);
			down_(data);
		}
		else if (!ft_strncmp(move, "right", 4))
		{
			check_exit_(data->py, data->px + 1, data);
			right_(data);
		}
		else if (!ft_strncmp(move, "left", 4))
		{
			check_exit_(data->py, data->px - 1, data);
			left_(data);
		}
	}
}

void	up_(t_data *data)
{
	int (w), (h);
	mlx_destroy_image(data->mlx_ptr, data->player);
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, PU_PATH, &w, &h);
	data->map[data->py][data->px] = '0';
	if (data->map[data->py - 1][data->px] == 'C')
		data->coins_count--;
	data->map[data->py - 1][data->px] = 'P';
	data->py--;
}

void	down_(t_data *data)
{
	int (w), (h);
	mlx_destroy_image(data->mlx_ptr, data->player);
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, PD_PATH, &w, &h);
	data->map[data->py][data->px] = '0';
	if (data->map[data->py + 1][data->px] == 'C')
		data->coins_count--;
	data->map[data->py + 1][data->px] = 'P';
	data->py++;
}

void	right_(t_data *data)
{
	int (w), (h);
	mlx_destroy_image(data->mlx_ptr, data->player);
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, PR_PATH, &w, &h);
	data->map[data->py][data->px] = '0';
	if (data->map[data->py][data->px + 1] == 'C')
		data->coins_count--;
	data->map[data->py][data->px + 1] = 'P';
	data->px++;
}

void	left_(t_data *data)
{
	int (w), (h);
	mlx_destroy_image(data->mlx_ptr, data->player);
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, PL_PATH, &w, &h);
	data->map[data->py][data->px] = '0';
	if (data->map[data->py][data->px - 1] == 'C')
		data->coins_count--;
	data->map[data->py][data->px - 1] = 'P';
	data->px--;
}

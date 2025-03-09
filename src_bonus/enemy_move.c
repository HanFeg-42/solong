/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:56:34 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/09 18:03:32 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move_enemy(t_data *data)
{
	int			x;
	int			y;
	static int	dir = -1;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'M')
				handle_enemy_move(data, y, &x, &dir);
			x++;
		}
		y++;
	}
}

void	handle_enemy_move(t_data *data, int y, int *x, int *dir)
{
	if (*dir == 1 && is_enemy_move_valid(data, y, *x, *dir))
	{
		data->map[y][*x] = '0';
		data->map[y][*x + (*dir)] = 'M';
		(*x) += 2;
	}
	else if (*dir == -1 && is_enemy_move_valid(data, y, *x, *dir))
	{
		data->map[y][*x] = '0';
		data->map[y][*x + (*dir)] = 'M';
		(*x)++;
	}
	else
		*dir = (*dir) * (-1);
}

int	is_enemy_move_valid(t_data *data, int y, int x, int dir)
{
	if (data->map[y][x + dir] == '0')
		return (1);
	else if (data->map[y][x + dir] == 'P')
	{
		ft_printf("\033[31mGame Over! You LOST\033[0m\n");
		exit_game(data);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:30:14 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 23:26:52 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	throw_error(char *err)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	clean_up(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	clean_and_exit(char **map, char *err)
{
	clean_up(map);
	throw_error(err);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 20:20:34 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	is_line_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] == '\0' && line [i] == '\n')
			break ;
		if (line[i] != '1')
			throw_error("unvalid map : check top and bottom walls\n");
		i++;
	}
}

char	**copy_map(t_map_data data)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (data.height + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (data.m[i])
	{
		ret[i] = ft_strdup(data.m[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	init_player_position(t_map_data *data)
{
	int (x), (y);
	y = 0;
	while (data->m[y])
	{
		x = 0;
		while (data->m[y][x])
		{
			if (data->m[y][x] == 'P')
			{
				data->x = x;
				data->y = y;
			}
			x++;
		}
		y++;
	}
}

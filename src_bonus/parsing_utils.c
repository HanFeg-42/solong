/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/07 23:08:51 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_player_exit_pos_(t_data *data)
{
	int (x), (y);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->px = x;
				data->py = y;
			}
			if (data->map[y][x] == 'E')
			{
				data->ex = x;
				data->ey = y;
			}
			x++;
		}
		y++;
	}
}

char	**copy_map_(t_data data)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (data.height + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (data.map[i])
	{
		ret[i] = ft_strdup(data.map[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	not_rectang(t_data *data, char *line)
{
	free(line);
	free(data->join);
	get_next_line(data->fd, 1);
	throw_error("it is not rectangular!\n");
}

void	is_line_valid_(t_data *data, int index, int size)
{
	int		i;
	char	*emoji;

	emoji = "10PCEM";
	i = 0;
	if (size != (int)ft_strlen(data->map[index])
		|| data->map[index][0] != '1' || data->map[index][size - 1] != '1')
		clean_and_exit(data->map, "unvalid wall\n");
	while (data->map[index][i + 1])
	{
		if (!ft_strchr(emoji, data->map[index][i]))
			clean_and_exit(data->map, "a character is not in {10PCEM}\n");
		i++;
	}
}

void	is_line_wall_(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] == '\0' && line [i] == '\n')
			break ;
		if (line[i] != '1')
			clean_and_exit(data->map, "unvalid map!\n");
		i++;
	}
}

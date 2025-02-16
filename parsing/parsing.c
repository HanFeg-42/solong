/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/16 10:56:45 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *is_map_valid(char *map)
{
	char	*err;
	int fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		perror_exit("failed to open");
	if ((err = only_3_componenmts(map)))
		return (err);
	if ((err = exit__start_position(map)))
		return (err);
	if ((err = only_3_componenmts(map)))
		return (err);
	if ((err = only_6_characters(map)))
		return (err);
	if ((err = is_rectangular(map)))
		return (err);
	if ((err = is_surrounded_by_walls(map)))
		return (err);
	if ((err = is_valid_path(map)))
		return (err);
	return (NULL);
}

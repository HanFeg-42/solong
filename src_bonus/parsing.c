/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:00:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/06 11:36:41 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int is_map_valid_(t_data *data)
{
	open_map_(data);
	get_map_(data);
}
void open_map_(t_data *data)
{
	check_map_ext(data->map_name);
	data->fd = open(data->map_name, O_RDONLY);
	if (data->fd < 0)
		perror_exit("failed to open");
}

void get_map_(t_data *data)
{
	
}
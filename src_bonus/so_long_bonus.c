/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:26:12 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/06 15:39:03 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (ft_putstr_fd("Unvalid arguments!", 2), 1);
	init0_data(av[1], &data);
	is_map_valid_(&data);
	printf("\033[32m map is valid congrats! \033[0m\n");
	// so_long_(&data);
	return (0);
}

void	init0_data(char *arg, t_data *data)
{
	data->map_name = arg;
	data->height = 0;
}


//TODO : 1 - bonus parsing -----------------------> DONE
//TODO : 2 - render the game
//TODO : 3 - display moves on window
//TODO : 4 - coin animation
//TODO : 5 - handle enemy behavior

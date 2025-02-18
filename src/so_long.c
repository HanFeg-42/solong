/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/16 10:45:09 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int main(int ac, char **av)
{
	t_solong    var;
	if (ac != 2 || check_map_ext(av[1]))
		throw_error("Error\nunvalid argument!\n");
	if ((var.err = is_map_valid(av[1])))
		throw_error(var.err);
	print_map(av[1]);
	return (0);
}
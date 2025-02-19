/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:57:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/19 01:17:33 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int main(int ac, char **av)
{
	t_solong    var;
	if (ac != 2)
		throw_error("unvalid argument!\n");
	if ((var.err = is_map_valid(av[1])))
		throw_error(var.err);
	printf("\033[32m map is valid congrats! \033[0m\n");
	return (0);
}
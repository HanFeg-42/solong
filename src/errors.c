/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:30:14 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/05 01:33:40 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	throw_error(char *err)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *err)
{
	perror(err);
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

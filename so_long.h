/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:01:30 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/16 10:40:19 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <stdbool.h>

//struct
typedef struct s_solong
{
	char *err;
}	t_solong;

typedef struct s_map_data
{
	char **m;
	int count;
	int x;
	int y;
}	t_map_data;



//parsing
char	*is_map_valid(char *map);
void	throw_error(char *err);
void	perror_exit(char *err);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:01:30 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/19 01:23:16 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <stdbool.h>

# define BUFFER_SIZE 1000000

//struct
typedef struct s_solong
{
	char *err;
}	t_solong;

typedef struct s_map_data
{
	char **m;
	int count;
	int height;
	int x;
	int y;
}	t_map_data;



//parsing
char	*is_map_valid(char *map);
void	check_map_ext(char *map);
void	throw_error(char *err);
void	perror_exit(char *err);
void	clean_up(char **str);
char	*get_next_line(int fd, int f);
int		recursion(char **map_data, int x, int y, int *count);
char	**get_map(int fd, t_map_data *data);
void	check_element(char *line, char c, int *character, t_map_data *data);
void	is_line_wall(char *line);
void	is_line_valid(char *line, int size);
char	*is_map_valid(char *map);


#endif
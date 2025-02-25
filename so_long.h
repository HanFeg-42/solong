/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:01:30 by hfegrach          #+#    #+#             */
/*   Updated: 2025/02/25 01:00:19 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
// # include <mlx.h>
# include <X11/keysym.h>
# include <stdbool.h>

# define BUFFER_SIZE 1000000
# define SCALE 64
# define PATH_WALL "../textures/wall.xpm"
# define PATH_FLOOR "../textures/floor.xpm"
# define PATH_PLAYER "../textures/player.xpm"
# define PATH_EXIT "../textures/exit.xpm"
# define PATH_COLLECTIBLE "../textures/collectible.xpm"

//struct
typedef struct s_solong
{
	char **map;
	char *err;
}	t_solong;

typedef struct s_map_data
{
	char **m;
	int count;
	int width;
	int height;
	int x;
	int y;
}	t_map_data;

typedef struct s_map
{
	char **m;
	int count;
	int width;
	int height;
	int x;
	int y;
}				t_map;


typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *mlx_win;
	void *images[5];
	t_map *map;
} t_mlx_data;

//parsing
char	*is_map_valid(char *map, t_solong *var);
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
// char	*is_map_valid(char *map);
void print_map(char **map);
char **copy_map(t_map_data data);

//so_long
void	loading_images(t_mlx_data *data);
void	rendering_to_win(t_mlx_data *data);
void	init_map_data(t_mlx_data *data, char **map);
void	so_long(char **map);
int		key_press(int key, t_mlx_data *data);
int		close_window(t_mlx_data *data);
char **copy_map_(char **map);


#endif
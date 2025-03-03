/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:01:30 by hfegrach          #+#    #+#             */
/*   Updated: 2025/03/03 00:10:44 by hfegrach         ###   ########.fr       */
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
# define PATH_WALL "textures/wall1.xpm"
# define PATH_FLOOR "textures/floor1.xpm"
# define PATH_PLAYER "textures/player1.xpm"
# define PATH_EXIT "textures/exit1.xpm"
# define PATH_COLLECTIBLE "textures/collectible1.xpm"
# define ARROW_U 65362
# define ARROW_D 65364
# define ARROW_R 65363
# define ARROW_L 65361

//struct
typedef struct s_solong
{
	char **map;
	char *err;
	int	coins;
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
	void *images[6];
	// t_map *map;
	char **map;
	int px;
	int py;
	int ex;
	int ey;
	int coins;
} t_mlx_data;

//parsing
char	*is_map_valid(char *map, t_solong *var);
void	check_map_ext(char *map);
void	throw_error(char *err);
void	perror_exit(char *err);
void	clean_up(char **str);
char	*get_next_line(int fd, int f);
int		recursion(char **map_data, int x, int y, int *count);
// char	**get_map(int fd);
char	**get_map(int fd, t_map_data *data);
void	check_element(char *line, char c, int *character, t_map_data *data);
void	is_line_wall(char *line);
void	is_line_valid(char *line, int size);
void	check_map(t_map_data *data);
void is_map_rect(t_map_data *data);
void is_player_valid(t_map_data *data);
void is_exit_valid(t_map_data *data);
void is_collectible_valid(t_map_data *data);


// char	*is_map_valid(char *map);
void print_map(char **map);
char **copy_map(t_map_data data);

//so_long
void	loading_images(t_mlx_data *data);
int	rendering_to_win(t_mlx_data *data);
void	so_long(t_mlx_data *(data));
int		key_press(int key, t_mlx_data *data);
int		close_window(t_mlx_data *data);
int is_move_valid(char *move, t_mlx_data *data);
void move_player(char *move, t_mlx_data *data);
int	check_exit(char *move, t_mlx_data *data);


#endif
#include <mlx.h>
#include "../so_long.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_mlx_image
{
	char	*relative_path;
	int		img_width;
	int		img_height;
}               t_mlx_image;



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int close_window(t_mlx_data *data)
{
    printf("you clicked red cross\n");
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (1);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
    t_mlx_data data;
    t_mlx_image xpm;

	mlx = mlx_init();
    data.mlx_ptr = mlx;
	mlx_win = mlx_new_window(mlx, 920, 880, "Hello world!");
    data.mlx_win = mlx_win;
    xpm.relative_path = "./gojo_saturu.xpm";
	// img.img = mlx_new_image(mlx, 920, 880);
    img.img = mlx_xpm_file_to_image(mlx, xpm.relative_path, &xpm.img_width, &xpm.img_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    mlx_string_put(mlx, mlx_win, 420, 75, 0xFFFFFF, "Goju Saturu");
	mlx_put_image_to_window(mlx, mlx_win, img.img, 75, 100);
    mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	mlx_loop(mlx);
}

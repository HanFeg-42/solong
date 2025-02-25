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


int    key_press(int key, t_mlx_data *data)
{
    if (key == XK_Escape)
    {
        printf("you pressed ESC\n");
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(0);
    }
    return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
    t_mlx_data data;
    t_mlx_image xpm;
	void *img2;
	char *rp;
	int w;
	int h;
	void *img3;
	int w3;
	int h3;
	char *rp3;

	mlx = mlx_init();
    data.mlx_ptr = mlx;
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
    data.mlx_win = mlx_win;
    xpm.relative_path = "./gojo_saturu.xpm";
	rp = "./winter.xpm";
	rp3 = "./spring_square.xpm";
	int wp, hp;
	// img.img = mlx_new_image(mlx, 920, 880);
    img.img = mlx_xpm_file_to_image(mlx, xpm.relative_path, &xpm.img_width, &xpm.img_height);
    // img2 = mlx_xpm_file_to_image(mlx, rp, &w, &h);
    // img3 = mlx_xpm_file_to_image(mlx, rp3, &w3, &h3);
	// void *imgp = mlx_xpm_file_to_image(mlx, "./pandaa.xpm", &wp, &hp);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 							&img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    mlx_string_put(mlx, mlx_win, 420, 75, 0xFFFFFF, "Goju Saturu");
	mlx_put_image_to_window(mlx, mlx_win, img.img, 75, 100);
	// int i;
	// int j = 1;
	// while (j < 880)
	// {
	// 	i = 1;
	// 	while (i < 920)
	// 	{
	// 		if (i <= 50 || j <= 50 || i >= 750 || j >= 550)
	// 			mlx_put_image_to_window(mlx, mlx_win, img2, i, j);
	// 		else
	// 			mlx_put_image_to_window(mlx, mlx_win, img3, i, j);
	// 		i = i +  64;
	// 	}
	// 	j = j + 64;
	// }
	// mlx_put_image_to_window(mlx, mlx_win, imgp, 64, 64);
	// mlx_put_image_to_window(mlx, mlx_win, img2, 1, 1);
    mlx_hook(data.mlx_win, 17, 0, close_window, &data);
    mlx_key_hook(data.mlx_win, key_press, &data);
	mlx_loop(mlx);
}

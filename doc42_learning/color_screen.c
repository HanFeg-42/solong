#include "../so_long.h"

typedef struct t_img
{
    void *img_ptr;
    char *img_pixels_ptr;
    int bits_per_pixel;
    int endian;
    int line_len;
} t_img;

typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *mlx_win;
    t_img img;
} t_mlx_data;

void my_pixel_put(t_img *img, int x, int y, int color)
{
    int offset;
    offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
    *((unsigned int *)(img->img_pixels_ptr + offset)) = color;

}

void color_screen(t_mlx_data *data, int color)
{
    int y = 0;
    int x = 0;
    while(y < 800)
    {
        x = 0;
        while(x < 800)
        {
            my_pixel_put(&data->img, x, y, color);
            x++;
        }
        y++;
    }
    // for (int y = 0; y < 800; ++y)
    // {
    //     for (int x = 0; x < 800; ++x)
    //     {
    //         my_pixel_put(&data->img,
    //                     x,
    //                     y,
    //                     color);
    //     }
    // }
}

int press_key(int keysym, t_mlx_data *data)
{
    if(keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(1);
    }
    else if (keysym == XK_r)
    {
        color_screen(data, 0xff0000);
    }
    else if(keysym == XK_g)
    {
        color_screen(data, 0x00ff00);
    }
    else if (keysym == XK_b)
    {
        color_screen(data, 0x0000ff);
    }
    else if (keysym == XK_p)
    {
        color_screen(data, 0x800080);
    }
    else if (keysym == XK_y)
    {
        color_screen(data, 0xffff00);
    }
    else if (keysym == XK_k)
    {
        color_screen(data, 0xff69b4);
    }
    else if (keysym == XK_o)
    {
        color_screen(data, 0xffa500);
    }
    else if (keysym == XK_c)
    {
        color_screen(data, 0x00ffff);
    }
    printf("The %d key has been pressed\n\n", keysym);

    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img_ptr, 0, 0);
    return (0);
}

int main()
{
    t_mlx_data data;

    data.mlx_ptr = mlx_init();//if(!ptr)
    data.mlx_win = mlx_new_window(data.mlx_ptr, 800, 800, "hello prety !");//if(!)

    data.img.img_ptr = mlx_new_image(data.mlx_ptr, 800, 800);
    data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);
    // img.img_pixels_ptr = pointer to the first pixel of the window
    mlx_key_hook(data.mlx_win, press_key, &data);
    mlx_loop(data.mlx_ptr);
}
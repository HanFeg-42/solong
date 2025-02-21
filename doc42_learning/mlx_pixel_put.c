#include "../minilibx-linux/mlx.h"
#include "../so_long.h"

#define size_x 800
#define size_y 600

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

int resize_window(int width, int height, void *param)
{
    (void)param;
    printf("window resized new width: %d, new height: %d\n", width, height);
    return (0);
}

int close_window(t_mlx_data *data)
{
    printf("you pressed ESC\n");
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (1);
}

int main()
{
    t_mlx_data mlx;

    mlx.mlx_ptr = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, size_x, size_y, "window 1");
    int x = 0;
    int y = 0;
    while (y < size_y)
    {
        x = 0;
        while (x < size_x)
        {
            mlx_pixel_put(mlx.mlx_ptr, mlx.mlx_win, x, y, 0xFF0000);
            x++;
        }
        usleep(100);
        y++;
    }
    mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
    // mlx_hook(mlx.mlx_win, 22, 0, resize_window, NULL);
    mlx_key_hook(mlx.mlx_win, key_press, &mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}
#include "../minilibx-linux/mlx.h"
#include "../so_long.h"

#define size_x 800
#define size_y 600

int main()
{
    void    *mlx_ptr;
    void    *window1;

    mlx_ptr = mlx_init();
    window1 = mlx_new_window(mlx_ptr, size_x, size_y, "window 1");
    int x = 0;
    int y = 0;
    while (y < size_y)
    {
        x = 0;
        while (x < size_x)
        {
            mlx_pixel_put(mlx_ptr, window1, x, y, 0xFF0000);
            x++;
        }
        usleep(100);
        y++;
    }
    return (0);
}
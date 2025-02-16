#include "../minilibx-linux/mlx.h"
#include "../so_long.h"

#define size_x 800
#define size_y 600

int main()
{
    void    *mlx_ptr;
    void    *window1;
    void    *window2;

    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return (1);
    window1 = mlx_new_window(mlx_ptr, size_x, size_y, "window 1");
    if (!window1)
    {
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return (1);
    }
    window2 = mlx_new_window(mlx_ptr, size_x, size_y, "window 2");
    if (!window2)
    {
        mlx_destroy_window(mlx_ptr, window1);
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return (1);
    }
    mlx_loop(mlx_ptr);
    // EVENT LOOP
    // without this loop the process will stop immediately
    // mlx_destroy_window(mlx_ptr, window1);
    // mlx_destroy_display(mlx_ptr);
    // free(mlx_ptr);
    return (0);
}
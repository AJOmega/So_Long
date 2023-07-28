#include "./minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_game
{
    void *mlx;
    void *win;
} t_game;
	
void render(t_game *game)
{
    mlx_pixel_put(game->mlx, game->win, 320, 240, 0xFF0000); // Draw a red pixel at (320, 240)
}

int game_loop(t_game *game)
{
    render(game); // Render the graphics
    return (0);
}

int main(void)
{
    t_game *game;

    game = (t_game*)malloc(sizeof(t_game));
    if (!game)
    {
        printf("Error: Failed to allocate memory.\n");
        return (1);
    }
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize mlx.\n");
        free(game);
        return (1);
    }
    game->win = mlx_new_window(game->mlx, 640, 480, "so_long");
    if (!game->win)
    {
        printf("Error: Failed to create window.\n");
        mlx_destroy_display(game->mlx);
        free(game);
        return (1);
    }
    mlx_loop_hook(game->mlx, game_loop, game); // Register the game_loop function
    mlx_loop(game->mlx); // Start the mlx loop
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game);
    return (0);
}
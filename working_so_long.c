#include "./minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100 // Map
#define MAX_COLS 100 // Map
#define IMAGE_SIZE 32 // Size of each image tile

typedef struct s_game
{
    void *mlx;
    void *win;
} t_game;

// Begin of Map

typedef struct
{
    int row;
    int col;
} Position;

typedef struct
{
    Position playerPos;
    Position exitPos;
    Position collectiblePos[MAX_ROWS * MAX_COLS];
    int numCollectibles;
    char map[MAX_ROWS][MAX_COLS + 1];
} GameMap;

GameMap parseMapFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    GameMap map;
    map.numCollectibles = 0;

    int row = 0;
    char line[MAX_COLS + 1];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (row >= MAX_ROWS)
        {
            printf("Error: Map exceeds maximum number of rows.\n");
            exit(1);
        }
        int col = 0;
        for (int i = 0; line[i] != '\0'; i++)
        {
            char c = line[i];
            if (col >= MAX_COLS)
            {
                printf("Error: Map exceeds maximum number of columns.\n");
                exit(1);
            }
            if (c == 'P')
            {
                map.playerPos.row = row;
                map.playerPos.col = col;
                map.map[row][col] = 'P'; // Assign 'P' for player position
            }
            else if (c == 'E')
            {
                map.exitPos.row = row;
                map.exitPos.col = col;
                map.map[row][col] = 'E'; // Assign 'E' for exit position
            }
            else if (c == 'C')
            {
                map.collectiblePos[map.numCollectibles].row = row;
                map.collectiblePos[map.numCollectibles].col = col;
                map.numCollectibles++;
                map.map[row][col] = 'C'; // Assign 'C' for collectible positions
            }
            else
            {
                map.map[row][col] = c;
            }
            col++;
        }
        row++;
    }

    fclose(file);
    return map;
}

// End of Map

void render(t_game *game, GameMap map, void *image_wall, void *image_player, void *image_exit, void *image_collectible, void *image_background, float scaleX, float scaleY)
{
    mlx_put_image_to_window(game->mlx, game->win, image_background, 0, 0);

    int row, col;
    for (row = 0; row < MAX_ROWS; row++)
    {
        for (col = 0; col < MAX_COLS; col++)
        {
            if (map.map[row][col] == '1')
            {
                // Draw a wall
                mlx_put_image_to_window(game->mlx, game->win, image_wall, col * scaleX,  row * scaleY);
            }
            else if (map.map[row][col] == 'P')
            {
                // Draw the player
                mlx_put_image_to_window(game->mlx, game->win, image_player, col * scaleX, row * scaleY); 
            }
            else if (map.map[row][col] == 'E')
            {
                // Draw the exit
                mlx_put_image_to_window(game->mlx, game->win, image_exit, col * scaleX, row * scaleY);
            }
            else if (map.map[row][col] == 'C')
            {
                // Draw the collectible
                mlx_put_image_to_window(game->mlx, game->win, image_collectible, col * scaleX, row * scaleY);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    const char *mapFile = argv[1];

    // Initialize game and window
    t_game *game = (t_game *)malloc(sizeof(t_game));
    game->mlx = mlx_init();

    // Parse the map file
    GameMap map = parseMapFile(mapFile);

    // Calculate the window size based on the map size
    int windowWidth = map.playerPos.col * IMAGE_SIZE;
    int windowHeight = map.playerPos.row * IMAGE_SIZE;

    // Create the window with the calculated size
    game->win = mlx_new_window(game->mlx, windowWidth, windowHeight, "So Long");

    // Load images
    void *image_wall = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &(int){IMAGE_SIZE}, &(int){IMAGE_SIZE});
    void *image_player = mlx_xpm_file_to_image(game->mlx, "player.xpm", &(int){IMAGE_SIZE}, &(int){IMAGE_SIZE});
    void *image_exit = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &(int){IMAGE_SIZE}, &(int){IMAGE_SIZE});
    void *image_collectible = mlx_xpm_file_to_image(game->mlx, "collectible.xpm", &(int){IMAGE_SIZE}, &(int){IMAGE_SIZE});
    void *image_background = mlx_xpm_file_to_image(game->mlx, "background.xpm", &(int){windowWidth}, &(int){windowHeight});

    // Render initial state
    render(game, map, image_wall, image_player, image_exit, image_collectible, image_background, IMAGE_SIZE, IMAGE_SIZE);

    // Start event loop
    mlx_loop(game->mlx);

    return 0;
}

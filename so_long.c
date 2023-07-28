#include "so_long.h"

t_GameMap parseMapFile(const char *filename);
void ft_render(t_game *game, t_GameMap map, void *image_wall, void *image_player, void *image_exit, void *image_collectible, void *image_background, float scaleX, float scaleY);
int	ft_input(int key, t_GameMap *gameMap);
void	ft_player_move(t_GameMap *gameMap, int new_x, int new_y);

t_GameMap parseMapFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    t_GameMap map;
    map.numCollectibles = 0;

    char line[MAX_COLS + 1];
    int x = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (x >= MAX_ROWS)
        {
            printf("Error: Map exceeds maximum number of rows.\n");
            exit(1);
        }
        int y = 0;
        for (int i = 0; line[i] != '\0'; i++) // NEED To change to WHILE
        {
            char c = line[i];
            if (y >= MAX_COLS)
            {
                printf("Error: Map exceeds maximum number of columns.\n");
                exit(1);
            }
            if (c == PLAYER)
            {
                map.playerPos.x = x;
                map.playerPos.y = y;
                map.map[x][y] = PLAYER; // Assign PLAYER for player t_position
            }
            else if (c == EXIT)
            {
                map.exitPos.x = x;
                map.exitPos.y = y;
                map.map[x][y] = EXIT; // Assign EXIT for exit t_position
            }
            else if (c == COLLECTIBLE)
            {
                map.collectiblePos[map.numCollectibles].x = x;
                map.collectiblePos[map.numCollectibles].y = y;
                map.numCollectibles++;
                map.map[x][y] = COLLECTIBLE; // Assign COLLECTIBLE for collectible positions
            }
            else
            {
                map.map[x][y] = c;
            }
            y++;
        }
        x++;
    }
    fclose(file);
    return map;
}

void ft_render(t_game *game, t_GameMap map, void *image_wall, void *image_player, void *image_exit, void *image_collectible, void *image_background, float scaleX, float scaleY)
{
    mlx_put_image_to_window(game->mlx, game->win, image_background, 0, 0);
	int x, y;
    for (x = 0; x < MAX_ROWS; x++)  // NEED To change to WHILE
    {
        for (y = 0; y < MAX_COLS; y++) // NEED To change to WHILE
        {
            if (map.map[x][y] == WALL)
            {
                // Draw a wall
                mlx_put_image_to_window(game->mlx, game->win, image_wall, y * scaleX,  x * scaleY);
            }
            else if (map.map[x][y] == PLAYER)
            {
                // Draw the player
                mlx_put_image_to_window(game->mlx, game->win, image_player, y * scaleX, x * scaleY); 
            }
            else if (map.map[x][y] == EXIT)
            {
                // Draw the exit
                mlx_put_image_to_window(game->mlx, game->win, image_exit, y * scaleX, x * scaleY);
            }
            else if (map.map[x][y] == COLLECTIBLE)
            {
                // Draw the collectible
                mlx_put_image_to_window(game->mlx, game->win, image_collectible, y * scaleX, x * scaleY);
            }
        }
    }
}

// Input 
int	ft_input(int key, t_GameMap *gameMap)
{
	if (key == KEY_UP || key == KEY_W)
	{
		printf("Up");
		ft_player_move(gameMap, gameMap->playerPos.x, gameMap->playerPos.y - 1);
	}
	if (key == KEY_LEFT || key == KEY_A)
		ft_player_move(gameMap, gameMap->playerPos.x - 1, gameMap->playerPos.y);
	if (key == KEY_RIGHT || key == KEY_D)
		ft_player_move(gameMap, gameMap->playerPos.x + 1, gameMap->playerPos.y);
	if (key == KEY_DOWN || key == KEY_S)
		ft_player_move(gameMap, gameMap->playerPos.x, gameMap->playerPos.y + 1);
	// if (key == KEY_Q || KEY_ESQ)
	// 	ft_close_game(gameMap)
	return (0);
}

void	ft_player_move(t_GameMap *gameMap, int new_x, int new_y)
{
	//int last_x;
	//int last_y;

	//last_x = gameMap->playerPos.x;
	//last_y = gameMap->playerPos.y;

	//if (gameMap->map[new_x, new_y]) == EXIT && gameMap->map
	char new_position = gameMap->map[new_x][new_y];
	if (new_position == FLOOR || new_position == COLLECTIBLE)
	{
		gameMap->map[gameMap->playerPos.x][gameMap->playerPos.y] = FLOOR;
        gameMap->playerPos.x = new_x;
        gameMap->playerPos.y = new_y;
        gameMap->map[new_x][new_y] = PLAYER;
        gameMap->movements++;
	}
	// gameMap->playerPos.x = new_x;
	// gameMap->playerPos.y = new_y;
	// gameMap->movements++;

}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

	//map.movements = 0;

    const char *mapFile = argv[1];
    t_GameMap map = parseMapFile(mapFile);
    t_game *game;

	int windowWidth = MAX_ROWS * IMAGE_X; // NEED CHANGE
    int windowHeight = MAX_COLS * IMAGE_Y; // NEED CHANGE
    game = (t_game *)malloc(sizeof(t_game));
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, windowWidth, windowHeight, "So Long");

    // Load images
    void *image_wall = mlx_xpm_file_to_image(game->mlx, WALL_XPM, &(int){IMAGE_X}, &(int){IMAGE_Y});
    void *image_player = mlx_xpm_file_to_image(game->mlx, PLAYER_XPM, &(int){IMAGE_X}, &(int){IMAGE_Y});
    void *image_exit = mlx_xpm_file_to_image(game->mlx, EXIT_XPM, &(int){IMAGE_X}, &(int){IMAGE_Y});
    void *image_collectible = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_XPM, &(int){IMAGE_X}, &(int){IMAGE_Y});
	void *image_background = mlx_xpm_file_to_image(game->mlx, BACKGROUND_XPM, &(int){windowWidth}, &(int){windowHeight});


    // Render initial state
    ft_render(game, map, image_wall, image_player, image_exit, image_collectible, image_background, IMAGE_X, IMAGE_Y);

	//mlx_key_hook(game->win, ft_input, &map);

	mlx_hook(game->win, KeyPress, KeyPressMask, ft_input, &map);		// Not Working

    mlx_loop(game->mlx);

    return 0;
}
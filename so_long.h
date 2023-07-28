/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabreu-d <jabreu-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:47:57 by jabreu-d          #+#    #+#             */
/*   Updated: 2023/07/23 20:08:41 by jabreu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h> 
# include <X11/X.h>
# include <X11/keysym.h>

# define MAX_ROWS			50 			// Map -- Remove after
# define MAX_COLS			50 			// Map -- Remove after
# define IMAGE_X	 		32 			// Size on x of each image tile
# define IMAGE_Y			32 			// Size on y of each image tile

// write xev on terminal to find keycode

			// Movement

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP  			65362
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363
# define KEY_DOWN  			65364	

			// Close Window

# define KEY_Q				113
# define KEY_ESC  			65307

			// Sprites

# define WALL_XPM			"wall.xpm"
# define PLAYER_XPM			"player.xpm"
# define EXIT_XPM			"exit.xpm"
# define COLLECTIBLE_XPM	"collectible.xpm"
# define BACKGROUND_XPM		"background.xpm"

			// Map Characters

# define WALL				'1'
# define PLAYER				'P'
# define EXIT				'E'
# define COLLECTIBLE		'C'
# define FLOOR				'0'


			// Structs

typedef struct s_game
{
    void *mlx;
    void *win;
} t_game;

typedef struct s_Position
{
    int x;
    int y;
} t_Position;

typedef struct s_GameMap
{
    t_Position playerPos;
    t_Position exitPos;
    t_Position collectiblePos[MAX_ROWS * MAX_COLS];
    int numCollectibles;
    char map[MAX_ROWS][MAX_COLS + 1];
	int movements;
} t_GameMap;


#endif
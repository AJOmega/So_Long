NAME = so_long
SRCS = so_long.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
#LDFLAGS = -L./minilibx-linux -lmlx -L./Libft -lft -L/usr/lib -I./minilibx-linux -lX11 -lXext -lm
LDFLAGS = -L./minilibx-linux -lmlx -L./Libft -lft -lXext -lX11 -lm
#INCLUDES = -Imx-linux -I./
INCLUDES = -I./minilibx-linux -I./Libft

MLXFLAGS = -L. -lXext -L. -lX11

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

MINILIBX_PATH	=	./minilibx-linux
MINILIBX		=	$(MINILIBX_PATH)/libmlx.a

LIBFT_PATH		=	./Libft
libft			=	$(LIBFT_PATH)/libft.a

all: $(NAME)

# $(NAME): $(OBJS) libft
# 	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LDFLAGS) -o $(NAME)

$(NAME): libft MINILIBX $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(libft) $(MINILIBX) -o $(NAME) 

libft:
	make -C ./Libft

MINILIBX:
	make -C ./minilibx-linux

clean:
	rm -f $(OBJS)
	make -C minilibx-linux clean
	make -C ./Libft clean

fclean: clean
	rm -f $(NAME)
	make -C minilibx-linux clean
	make -C ./Libft fclean

re: fclean all

.PHONY: all clean fclean re

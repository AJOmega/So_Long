NAME = so_long.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

# SRC = 

# OBJ = $(SRC:.c=.o)

# BONUS = 

# BOBJ = $(BONUS:.c=.o)

# all:	$(NAME)

# bonus:	$(BOBJ)
# 			ar rcs $(NAME) $(BOBJ)

# $(NAME):	$(OBJ)
# 			ar rcs $(NAME) $(OBJ)

# clean:
# 			$(RM) $(OBJ) $(BOBJ)

# fclean:	clean
# 			$(RM) $(NAME) $(BOBJ)

re:	fclean $(NAME)
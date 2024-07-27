NAME	= cub3D
SRC		= cub3d.c cub3d_map.c cub3d_utils.c cub3d_map_2.c
OBJ		= $(SRC:.c=.o)
HEADER	= cub3d.h
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LINKS	= -lmlx -framework OpenGL -framework AppKit
RM		= rm -f
LIB = 	./lib/libft.a

all: pre $(NAME) clean

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) $(LINKS) -o $(NAME) $(LIB) -fsanitize=address

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

pre:
	@$(MAKE) -C lib

clean:
	$(MAKE) -C lib clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C lib fclean
	$(RM) $(NAME)

bonus:

re: fclean all

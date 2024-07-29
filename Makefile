NAME    = cub3D
SRC     = cub3d.c cub3d_map.c cub3d_utils.c cub3d_utils2.c cub3d_map2.c
OBJ     = $(SRC:.c=.o)
HEADER  = cub3d.h
CC      = cc
CFLAGS  = -Wall -Wextra -Werror 
LINKS   = ../MLX42/build/libmlx42.a -Iinclude -lglfw -L/Users/aghounam/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit
RM      = rm -f
LIB     = ./utils/libft.a
MLX     = ../MLX42/build/libmlx42.a

all:  $(NAME) $(LIB) $(MLX)

$(NAME): $(OBJ) $(LIB) $(MLX)
	$(CC) $(OBJ) $(LIB) $(LINKS) -o $(NAME)

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C utils

$(MLX):
	@cd ../MLX42/build && make

clean:
	$(MAKE) -C utils clean
	@cd ../MLX42/build && make clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C utils fclean
	$(RM) $(NAME)

re: fclean all

NAME	=	cub3D
SRC		=	cub3d.c cub3d_map.c cub3d_utils.c cub3d_utils2.c cub3d_map2.c ray_casting.c map.c init_exec.c mini_map.c rander_wall.c utils_exec.c
OBJ		=	$(SRC:.c=.o)
HEADER	=	cub3d.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -g
LINKS	=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit 
RM		=	rm -f
LIB		=	./utils/libft.a
MLX		=	../MLX42/build/libmlx42.a

all: $(LIB) $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	$(CC) $(OBJ) $(LIB) $(MLX) $(LINKS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C utils

$(MLX):
	@cd ../MLX42/build && make

clean:
	$(MAKE) -C utils clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C utils fclean
	$(RM) $(NAME)
	@cd ../MLX42/build && make clean

re: fclean all


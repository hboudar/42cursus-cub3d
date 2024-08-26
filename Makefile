NAME	=	cub3D
SRC		=	Bonus/cub3d.c Bonus/cub3d_map.c Bonus/cub3d_utils.c \
			Bonus/cub3d_utils2.c Bonus/cub3d_map2.c Bonus/ray_casting.c \
			Bonus/map.c Bonus/init_exec.c Bonus/mini_map.c Bonus/rander_wall.c \
			Bonus/utils_exec.c
OBJ		=	$(SRC:.c=.o)
HEADER	=	cub3d.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -fsanitize=address -g
LINKS	=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit 
RM		=	rm -f
LIB		=	./utils/libft.a
MLX		=	../MLX42/build/libmlx42.a

all: $(LIB) $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	$(CC) $(OBJ) $(LIB) $(MLX) $(LINKS) -o $(NAME) -fsanitize=address -g

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


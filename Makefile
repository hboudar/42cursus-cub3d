NAME	=	cub3D
SRC		=	cub3d.c \
			mandatory/map.c mandatory/map2.c mandatory/utils.c mandatory/utils_error.c
OBJ		=	$(SRC:.c=.o)
HEADER	=	cub3d.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
LINKS	=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit 
RM		=	rm -f
LIB		=	./utils/libft.a
MLX		=	../../MLX42/build/libmlx42.a

all: $(LIB) $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	$(CC) $(OBJ) $(LIB) $(MLX) $(LINKS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C utils
$(MLX):
	@cd ../MLX42 && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C utils clean
	$(RM) $(OBJ)

fclean: clean
	@cd utils && make fclean
	$(RM) $(NAME)

re: fclean all

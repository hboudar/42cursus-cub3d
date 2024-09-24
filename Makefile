NAME	=	cub3D
SRC		=	cub3d.c \
			_Parsing/mandatory/parsing1.c _Parsing/mandatory/parsing2.c _Parsing/mandatory/parsing_utils.c \
			_Execution/mandatory/execution.c _Execution/mandatory/key_pressed.c _Execution/mandatory/ray_casting.c \
			_Execution/mandatory/render.c _Execution/mandatory/execution_utils.c \
			_Utils/error.c
OBJ		=	$(SRC:.c=.o)
HEADER	=	includes/cub3d.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
LINKS	=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit 
RM		=	rm -f
LIB		=	./_Utils/libft.a
MLX		=	../../MLX42/build/libmlx42.a

all: $(LIB) $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	$(CC) $(OBJ) $(LIB) $(MLX) $(LINKS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C _Utils
$(MLX):
	@cd ../../MLX42 && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C _Utils clean
	$(RM) $(OBJ)

fclean: clean
	@cd _Utils && make fclean
	$(RM) $(NAME)
# @cd ../../MLX42 && rm -rf build

re: fclean all

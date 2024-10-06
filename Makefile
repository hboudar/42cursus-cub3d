NAME			=	cub3D
SRC				=	cub3d.c \
					_Parsing/mandatory/parsing1.c _Parsing/mandatory/parsing2.c _Parsing/mandatory/parsing_utils.c \
					_Execution/mandatory/execution.c _Execution/mandatory/key_pressed.c _Execution/mandatory/ray_casting.c \
					_Execution/mandatory/render.c _Execution/mandatory/execution_utils.c \
					Utils/error.c
OBJ				=	$(SRC:.c=.o)
HEADER			=	includes/cub3d.h

NAME_BONUS		=	cub3D_bonus
SRC_BONUS		=	cub3d_bonus.c \
					_Parsing/bonus/parsing1_bonus.c _Parsing/bonus/parsing2_bonus.c _Parsing/bonus/parsing_utils_bonus.c \
					_Execution/bonus/execution_bonus.c _Execution/bonus/key_pressed_bonus.c _Execution/bonus/ray_casting_bonus.c \
					_Execution/bonus/render_bonus.c _Execution/bonus/mini_map_bonus.c _Execution/bonus/execution_utils_bonus.c \
					Utils/error_bonus.c

OBJS_BONUS		=	${SRC_BONUS:_bonus.c=_bonus.o}
HEADER_BONUS	=	includes/cub3d_bonus.h

CC				=	cc
RM				=	rm -f
LIB				=	Utils/libft.a
CFLAGS			=	-Wall -Wextra -Werror -g 
MLX				=	../../MLX42/build/libmlx42.a
LINKS			=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit 

all: $(LIB) $(MLX) $(NAME)

bonus: $(LIB) $(MLX) $(NAME_BONUS)

$(NAME): $(OBJ) $(LIB) $(MLX)
	$(CC) $(OBJ) $(LIB) $(MLX) $(LINKS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIB) $(MLX)
	$(CC) $(OBJS_BONUS) $(LIB) $(MLX) $(LINKS) -o $(NAME_BONUS)

%_bonus.o: %_bonus.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C Utils
$(MLX):
	@cd ../../MLX42 && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C Utils clean
	$(RM) $(OBJ) $(OBJS_BONUS)

fclean: clean
	@cd Utils && make fclean
	$(RM) $(NAME) $(NAME_BONUS)
# @cd ../../MLX42 && rm -rf build

re: fclean all

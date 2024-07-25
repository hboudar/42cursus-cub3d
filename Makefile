NAME	= cub3D
SRC		= cub3d.c ft_map.c
OBJ		= $(SRC:.c=.o)
HEADER	= cub3d.h
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LINKS	= -lmlx -framework OpenGL -framework AppKit
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LINKS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

bonus:

re: fclean all

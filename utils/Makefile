NAME	=	libft.a
SRC		=	ft_strlen.c ft_memcpy.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c \
			ft_putstr_fd.c get_next_line.c get_next_line_utils.c
OBJS	=	${SRC:.c=.o}
LIBC	=	ar -rcs
CFLAGS	=	-Wall -Wextra -Werror
CC		=	cc
RM		=	rm -f

%.o: %.c libft.h
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} $(OBJS)

fclean: clean
		${RM} ${NAME}

re: fclean all


.PHONY: clean fclean all re

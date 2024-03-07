CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft -lft

SRCS = 

OBJS = ${SRCS:.c=.o}

NAME = so_long

${NAME}: ${OBJS}
	make -C libft
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
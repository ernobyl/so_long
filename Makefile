UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CC = gcc
	CFLAGS = -Wall -Wextra -Werror -Iinclude -pthread -lm
	LDFLAGS = -ldl -lglfw

	SRCS = example.c

	OBJS = ${SRCS:.c=.o}

	LIBMLX = linux-MLX42/libmlx42.a

	NAME = so_long

	${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${OBJS} ${LIBMLX} ${LDFLAGS} -o ${NAME}

	all: ${NAME}

	clean:
		rm -f ${OBJS}

	fclean: clean
		rm -f ${NAME}

	re: fclean all

	.PHONY: all clean fclean re
endif
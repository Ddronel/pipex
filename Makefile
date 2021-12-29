NAME = pipex

HEAD = pipex.h pipex_bonus.h ${LIBFT_PATH}libft.h

LIBFT_PATH = ./MyLib/

LIBFT = ${LIBFT_PATH}libft.a

FUNC = pipex.c pipex_utils.c

BONUS_FUNC = pipex_bonus.c pipex_utils_bonus.c

BONUS_OBJS = ${BONUS_FUNC:.c=.o}

OBJS	= ${FUNC:.c=.o}


CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

.PHONY: all clean fclean re bonus

all: ${NAME}

${LIBFT} :
			@ ${MAKE} -sC ${LIBFT_PATH}

${NAME}	:	${LIBFT} ${OBJS} ${HEAD}
			@ ${CC} ${CFLAGS} ${LIBFT} ${OBJS} -o ${NAME}

bonus:		${NAME} ${BONUS_FUNC} ${HEAD}
			${CC} ${CFLAGS} -c ${BONUS_FUNC}
			@ ${CC} ${CFLAGS} ${LIBFT} ${BONUS_OBJS} -o ${NAME}

clean :
			${RM} ${OBJS}
			${RM} ${BONUS_OBJS}
			@ ${MAKE} -C ${LIBFT_PATH} clean

fclean :	clean
			${RM} ${NAME}
			@ ${MAKE} -C ${LIBFT_PATH} fclean

re	:	fclean all clean bonus

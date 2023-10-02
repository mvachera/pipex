# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 21:10:02 by mvachera          #+#    #+#              #
#    Updated: 2023/09/10 17:05:39 by mvachera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

BONUS	= pipex_bonus

CC	= clang

CFLAGS  = -Wall -Wextra -Werror -g3

RM	= rm -f

LIBFT          = libft

FT_LIBFT	= libft/libft.a

PRINTF          = ft_printf

FT_PRINTF       = ft_printf/libftprintf.a

SRC     = srcs/main1.c srcs/utils1.c

BONUS_SRC	=  bonus/main.c bonus/utils.c bonus/utils2.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJ_BONUS	= ${BONUS_SRC:.c=.o}

OBJ     = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${MAKE} -C ${LIBFT}
	${MAKE} -C ${PRINTF}
	${CC} ${OBJ} -o ${NAME} ${FT_LIBFT} ${FT_PRINTF}

bonus : ${BONUS}

${BONUS} : ${OBJ_BONUS}
	${MAKE} -C ${LIBFT}
	${MAKE} -C ${PRINTF}
	${CC} ${OBJ_BONUS} -o ${BONUS} ${FT_LIBFT} ${FT_PRINTF}

clean :
	${RM} ${OBJ} ${OBJ_BONUS}

fclean : clean
	${RM} ${NAME} ${BONUS}

re : fclean all

.PHONY : all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxell <maxell@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 14:29:08 by rvoltigo          #+#    #+#              #
#    Updated: 2021/04/24 18:10:48 by maxell           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = gcc

NAME	=	so_long

HEADERS =	so_long.h	get_next_line.h

FLAGS	= 	-Wall -Wextra -Werror

SRC  = main.c \
    get_next_line.c \
    get_next_line_utils.c \
    utils_lib.c \
    utils_lib2.c 


OBJ		=	$(patsubst %.c, %.o, $(SRC))

all		:	$(NAME)

$(NAME)	:	$(SRC)
	gcc $(CFLAGS) -c $(SRC)
	gcc $(FLAGS) $(OBJ) -o -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -lmx

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(NAME) 

# re:		:	fclean $(NAME)
#  	fclean
# 	make all
	

.PHONY	:	all clean fclean re
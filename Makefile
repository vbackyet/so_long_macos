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

NAME_BONUS = so_long_bonus

HEADERS =	so_long.h	get_next_line.h

FLAGS	= 	-Wall -Wextra -Werror

SRC  = main.c \
    get_next_line.c \
    get_next_line_utils.c \
    utils_lib.c \
    utils_lib2.c \
	key_act.c \
	initial_act.c

SRC_BONUS = bonus_maker/main.c \
    get_next_line.c \
    get_next_line_utils.c \
    utils_lib.c \
    utils_lib2.c \
	key_act.c \
	bonus_maker/initial_act.c

OBJ		=	$(patsubst %.c, %.o, $(SRC))

all		:	$(NAME)

$(NAME)	:	$(SRC)
	gcc $(CFLAGS) -c $(SRC)
	gcc $(FLAGS) $(OBJ) -o -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -lmx
	
bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(SRC_BONUS)
	gcc $(CFLAGS) -c $(SRC_BONUS)
	gcc $(FLAGS) $(OBJ) -o -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS) -lmx


clean	:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean	:	clean
	rm -f $(NAME) 
	rm -f $(NAME_BONUS) 

re:	fclean all

.PHONY	:	all clean fclean re
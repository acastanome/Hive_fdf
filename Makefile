#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acastano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 18:52:33 by acastano          #+#    #+#              #
#    Updated: 2022/04/07 20:28:29 by acastano         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./libft/ -I ./fdf.h

LIB = -L ./libft -lft -L ~/Downloads/minilibx/ -lmlx -framework OpenGL -framework AppKit

SRC = main.c line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LIB) -o $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
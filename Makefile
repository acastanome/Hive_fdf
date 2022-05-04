#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acastano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 18:52:33 by acastano          #+#    #+#              #
#    Updated: 2022/05/04 13:31:29 by acastano         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./libft/ -I ./fdf.h

LIB = -L ./libft -lft -L ~/Downloads/minilibx/ -lmlx -framework OpenGL -framework AppKit

SRC = main.c read_file.c render_map.c line.c exit_fdf.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft/
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LIB) -o $(NAME)

clean:
	@make clean -C libft/
	/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 14:12:49 by mjeyavat          #+#    #+#              #
#    Updated: 2022/05/02 20:22:33 by mjeyavat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c window.c parser.c read_tools.c string_tools.c\

OBJ = $(SRC:.c=.o);

LINKED_OBJ = ./mlx/*.o

all: linked_objects $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -Lmlx -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a -o $(NAME)

objects:
	$(CC) $(CFLAGS) $(OBJ) $(LINKED_OBJ)

linked_objects:
	make -C ./mlx

clean:
	rm -f ./mlx/libmlx.a

fclean: clean
	rm -f $(NAME) ./mlx/*.o *.o

re: fclean all
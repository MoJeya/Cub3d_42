# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 14:12:49 by mjeyavat          #+#    #+#              #
#    Updated: 2022/05/09 10:35:49 by rschleic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c window.c parser.c read_tools.c string_tools.c\

OBJ = $(SRC:.c=.o);

LINKED_OBJ = ./mlx/*.o ./libft/*.o

all: linked_objects $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a -o $(NAME)

# objects:
# 	$(CC) $(CFLAGS) $(OBJ) $(LINKED_OBJ)

linked_objects:
	make -C ./libft
	make -C ./mlx

clean:
	rm -f ./libft/*.a ./mlx/libmlx.a

fclean: clean
	rm -f $(NAME) ./libft/*.o ./mlx/*.o *.o 

re: fclean all
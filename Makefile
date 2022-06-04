
NAME = cube3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -g

SRC = $(shell find *.c ./parser_stuff/*.c ./minimap/*.c ./raycasting/*.c)

OBJ = $(SRC:.c=.o);

LINKED_OBJ = ./NEW_MLX42/*.o ./libft/*.o parser_stuff/*.o

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo compiled $@

all: linked_objects $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(SRC) -Llibft -lft NEW_MLX42/libmlx42.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

# objects:
# 	$(CC) $(CFLAGS) $(OBJ) $(LINKED_OBJ)

linked_objects:
	make -C ./libft
	make -C ./NEW_MLX42

clean:
	rm -f ./libft/*.a ./NEW_MLX42/*.a 

fclean: clean
	rm -f $(NAME) *.o ./minimap/*.o ./parser_stuff/*.o ./libft/obj/*.o ./raycasting/*.o $(shell find ./NEW_MLX42/* -iname "*.o")

re: fclean all
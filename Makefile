
NAME = cub3D

CC = gcc

RED = "\033[0;31m"

X = "\033[0m"

CFLAGS = -Wall -Wextra -Werror -g3 -g

SRC = $(shell find *.c ./minimap/*.c ./raycasting/*.c) $(shell find ./parser_stuff/* -iname "*.c")

OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o,  $(SRC)));

OBJ_DIR = ./includes/obj/

LINKED_OBJ = ./includes/NEW_MLX42/*.o ./includes/libft/obj/*.o ./includes/obj/parser_stuff/*.o



$(OBJ_DIR)%.o: %.c
	@mkdir -p $$(dirname $@)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "\033[34mCompiling: $(shell basename "$(<)")\033[0m"

all: linked_objects $(NAME)
	@echo $(RED)
	@echo "...........................⣀⣤⣤⣤⣴⣶⡄....................."
	@echo "...................⣠⣤⣄⠀⣠⣴⡿⠋⢉⢙⠟⠛⠉⢿⣀⣠⡀.................."
	@echo ".................⣸⠃⠀⠊⢿⣿⡏⢠⣖⣉⢹⠀⣞⢀⡾⠋⡉⠋..................."
	@echo "...............⠐⢿⠀⠨⠀⢸⣿⣧⣌⢙⣛⠛⠚⡟⣓⠄⠠⣡⠗...................."
	@echo ".................⠹⢷⣤⣠⣼⣿⣿⣿⡾⢟⡉⠀⠋⠛⣦⠞⠁...................."
	@echo ".....................⢠⣿⣿⣿⠃⠀⠀⠀⠄⠀⢃......................."
	@echo "......................⢸⣿⡿⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀...................."
	@echo "......................⠸⣿⣇⠀⠀⠀⠀⠀⠀⣤⠀⡀⠀...................."
	@echo ".......................⣿⣿⣷⣦⡤⠤⣤⣬⣙⠖⠂....................."
	@echo "......................⢀⣾⣿⣿⣿⣿⡧⠄........................."
	@echo "..................⡀⢀⠙⠛⢿⣿⣿⣿⣿⣴⠑.........................."
	@echo "...............⡠⣤⠈⠀⠳⡄⠀⡀⢙⣙⣿⣿⣨⣼⠾⢐⡆......................"
	@echo "..............⠠⡀⡀⡀⠈⠠⢧⡀⠘⢁⠀⢿⣿⡟⡍⠀⢸⢣......................"
	@echo "..............⠆⠆⠀⠀⣸⠁⠀⠙⠀⠈⠲⡆⠸⠌⠟⠘⠚⠒......................"
	@echo "....................ROMO-CUB3D..........................."
	@echo $(X)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(SRC) ./includes/libft/libft.a ./includes/NEW_MLX42/libmlx42.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

linked_objects:
	make -C ./includes/libft
	make -C ./includes/NEW_MLX42

clean:
	rm -f ./includes/libft/*.a ./includes/NEW_MLX42/*.a 

fclean: clean
	rm -f $(NAME) *.o $(shell find ./includes/obj/* -iname "*.o") $(shell find ./includes/NEW_MLX42/* -iname "*.o")

re: fclean all
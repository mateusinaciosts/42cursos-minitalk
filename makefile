NAME = minitalk

NAME = fractol
FLAGS 			= -Wall -Wextra -Werror
LIBFTFLAGS 		= -L ./libft/ -lft

CLIENT = client
SRC_CLIENT = client.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SERVER = server
SRC_SERVER = server.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(CLIENT): $(OBJ_CLIENT)
	make -C libft
	cc $(FLAGS) -o $(CLIENT) $(OBJ_CLIENT) $(LIBFTFLAGS)
	
$(SERVER): $(OBJ_SERVER)
	make -C libft
	cc $(FLAGS) -o $(SERVER) $(OBJ_SERVER) $(LIBFTFLAGS) 

clean:
	rm $(OBJ_CLIENT) $(OBJ_SERVER)
	make clean -C libft

fclean: clean
	rm $(NAME) $(SERVER) $(CLIENT)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re

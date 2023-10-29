NAME = minitalk

CLIENT		= client
SRC_CLIENT	= client.c
OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

SERVER		= server
SRC_SERVER	= server.c
OBJ_SERVER	= $(SRC_SERVER:.c=.o)


CFLAGS   = -Wall -Wextra -Werror
LFLAGS	 = -L ./libft -lft
PFLAGS	 = -L ./printf -lftprintf
INCLUDES = -I ./ -I ./libft -I ./printf


all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(CLIENT): $(OBJ_CLIENT)
	make -C ./printf/
	make -C ./libft/
	cc $(OBJ_CLIENT) $(LFLAGS) $(PFLAGS) -o $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	make -C ./printf/
	make -C ./libft/
	cc $(OBJ_SERVER) $(LFLAGS) $(PFLAGS) -o $(SERVER)

%.o: %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm  -rf $(OBJ_CLIENT) $(OBJ_SERVER)
	make clean -C ./printf/
	make clean -C ./libft/

fclean: clean
	@rm -f $(NAME) $(SERVER) $(CLIENT)
	make fclean -C ./printf/
	make fclean -C ./libft/

re: fclean all

test:
	@clear
	@make re
	@clear
	./server
	
.PHONY: all clean fclean re


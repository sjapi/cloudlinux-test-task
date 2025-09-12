NAME=run_cmds

INCLUDE_DIR=./include/
SRC_DIR=./src/
OBJ_DIR=./obj/

HDR=$(addprefix $(INCLUDE_DIR), utils.h)
SRC=$(addprefix $(SRC_DIR), main.c validator.c execute.c utils.c)
OBJ=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o ,$(SRC))

CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR) 

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re 

HEADER_DIR		:= ./include/
SRC_DIR			:= ./src/
OBJ_DIR			:= ./obj/

_SRC 	:= main.c

SRC		:= $(addprefix $(SRC_DIR), $(_SRC))
OBJ		:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC			:= gcc
CFLAGS		:= -g -c -Wall -Wextra -Werror
CPPFLAGS	:= -I$(HEADER_DIR)

NAME := tpolonen.filler

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "Compiled objs"
	@$(CC) -o $@ $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR):
	@/bin/mkdir -p $@
	@echo "Made obj dir"

clean:
	@if [ -d "$(OBJ_DIR)" ]; \
		then /bin/rm -rf $(OBJ_DIR); echo "Removed objs"; fi

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Removed tpolonen.filler"

re: fclean all

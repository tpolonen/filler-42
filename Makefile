# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/01 19:35:15 by tpolonen          #+#    #+#              #
#    Updated: 2022/10/07 17:56:55 by tpolonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER_DIR		:= ./include/
LIBHEADER_DIR	:= ./libft/include/
LIB_DIR			:= ./libft/
SRC_DIR			:= ./src/
OBJ_DIR			:= ./obj/

_SRC 	:= main.c
_SRC 	+= utils.c
_SRC 	+= read.c
_SRC 	+= debug.c
_SRC 	+= player.c

DEP 	:= $(HEADER_DIR)filler.h

SRC		:= $(addprefix $(SRC_DIR), $(_SRC))
OBJ		:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC			:= gcc
CFLAGS		:= -g -c -Wall -Wextra -Werror
CPPFLAGS 	:= -I$(LIBHEADER_DIR) -I$(HEADER_DIR)
LDFLAGS 	:= -L$(LIB_DIR)
LDLIBS 		:= -lft

BIN := tpolonen.filler

.PHONY: all clean fclean re

all: lib $(BIN)

lib:
	@make -C $(LIB_DIR)
	@echo "Compiled library"

$(BIN): $(OBJ_DIR) $(OBJ)
	@echo "Compiled objs"
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)
	@echo "Compiled tpolonen.filler"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR):
	@/bin/mkdir -p $@
	@echo "Made obj dir"

clean:
	@if [ -d "$(OBJ_DIR)" ]; \
		then /bin/rm -rf $(OBJ_DIR); echo "Removed objs"; fi
	@make -C $(LIB_DIR) clean

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(BIN)
	@echo "Removed tpolonen.filler"

re: fclean all

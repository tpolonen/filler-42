# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/01 19:35:15 by tpolonen          #+#    #+#              #
#    Updated: 2023/01/30 20:22:00 by tpolonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER_DIR		:= ./include/
LIBHEADER_DIR	:= ./libft/include/
LIB_DIR			:= ./libft/
SRC_DIR			:= ./src/
OBJ_DIR			:= ./obj/

_SRC 	:= main.c
_SRC 	+= scout.c
_SRC 	+= strategist.c
_SRC 	+= tactician.c
_SRC 	+= captain.c

_SRC	+= counters.c
_SRC 	+= utils.c
_SRC 	+= debug.c
_SRC 	+= floodfill.c
_SRC 	+= storage.c

DEP 	:= $(HEADER_DIR)filler.h
DEP 	+= $(HEADER_DIR)structs.h

SRC		:= $(addprefix $(SRC_DIR), $(_SRC))
OBJ		:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC			:= gcc
CFLAGS		:= -g -c -Wall -Wextra -Werror 
CPPFLAGS 	:= -I$(LIBHEADER_DIR) -I$(HEADER_DIR) 
LDFLAGS 	:= -L$(LIB_DIR)
LDLIBS 		:= -lft

BIN := tpolonen.filler

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	CPPFLAGS += -DLINUX
endif

ifeq ($(OS), Windows_NT)
	CPPFLAGS += -DWIN
	BIN := tpolonen.exe
endif

.PHONY: all clean fclean re debug

all: $(LIB_DIR)libft.a $(BIN)

debug: CPPFLAGS += -DDEBUG_ON
debug: CFLAGS += -DDEBUG_ON
debug: LDFLAGS += -fsanitize=address -fsanitize=undefined \
	-fno-sanitize-recover=all -fno-sanitize=null -fno-sanitize=alignment 
debug: all

$(LIB_DIR)libft.a:
	@make -C $(LIB_DIR)
	@echo "Compiled library"

$(BIN): $(OBJ_DIR) $(OBJ)
	@echo "Compiled objs"
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)
	@echo "Compiled $(BIN)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

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
	@echo "Removed $(BIN)"

re: fclean all

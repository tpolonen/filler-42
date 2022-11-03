# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 19:01:12 by tpolonen          #+#    #+#              #
#    Updated: 2022/10/01 21:04:12 by tpolonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER_DIR = ./include/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

_SRC := ft_abs.c
_SRC += ft_atoi.c
_SRC += ft_bzero.c
_SRC += ft_calloc.c
_SRC += ft_dintarr.c
_SRC += ft_dstr.c
_SRC += ft_fabs.c
_SRC += ft_getline.c
_SRC += ft_intlen.c
_SRC += ft_isalnum.c
_SRC += ft_isalpha.c
_SRC += ft_isascii.c
_SRC += ft_isdigit.c
_SRC += ft_islower.c
_SRC += ft_isprint.c
_SRC += ft_isspace.c
_SRC += ft_isupper.c
_SRC += ft_itoa.c
_SRC += ft_lstadd.c
_SRC += ft_lstadd_back.c
_SRC += ft_lstcount.c
_SRC += ft_lstdel.c
_SRC += ft_lstdelone.c
_SRC += ft_lstiter.c
_SRC += ft_lstmap.c
_SRC += ft_lstnew.c
_SRC += ft_lstprint.c
_SRC += ft_max.c
_SRC += ft_memalloc.c
_SRC += ft_memccpy.c
_SRC += ft_memchr.c
_SRC += ft_memcmp.c
_SRC += ft_memcpy.c
_SRC += ft_memdel.c
_SRC += ft_memmove.c
_SRC += ft_memrchr.c
_SRC += ft_memset.c
_SRC += ft_putbit.c
_SRC += ft_putchar.c
_SRC += ft_putchar_fd.c
_SRC += ft_putendl.c
_SRC += ft_putendl_fd.c
_SRC += ft_putmem.c
_SRC += ft_putnbr.c
_SRC += ft_putnbr_fd.c
_SRC += ft_putnum.c
_SRC += ft_putset.c
_SRC += ft_putstr.c
_SRC += ft_putstr_fd.c
_SRC += ft_strcat.c
_SRC += ft_strchr.c
_SRC += ft_strchrnul.c
_SRC += ft_strclr.c
_SRC += ft_strcmp.c
_SRC += ft_strcpy.c
_SRC += ft_strdel.c
_SRC += ft_strdup.c
_SRC += ft_strequ.c
_SRC += ft_striter.c
_SRC += ft_striteri.c
_SRC += ft_strjoin.c
_SRC += ft_strlcat.c
_SRC += ft_strlcpy.c
_SRC += ft_strlen.c
_SRC += ft_strmap.c
_SRC += ft_strmapi.c
_SRC += ft_strncat.c
_SRC += ft_strncmp.c
_SRC += ft_strncpy.c
_SRC += ft_strnequ.c
_SRC += ft_strnew.c
_SRC += ft_strnstr.c
_SRC += ft_strrchr.c
_SRC += ft_strsplit.c
_SRC += ft_strstr.c
_SRC += ft_strsub.c
_SRC += ft_strtol.c
_SRC += ft_strtrim.c
_SRC += ft_tolower.c
_SRC += ft_toupper.c

SRC	:= $(addprefix $(SRC_DIR), $(_SRC))
OBJ	:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

DEP := $(HEADER_DIR)libft.h

CC = gcc
CFLAGS = -c -g -Wall -Wextra -Werror -I$(HEADER_DIR)
ARFLAGS = rcs

NAME = libft.a

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	CPPFLAGS += -DLINUX
endif

ifeq ($(OS), Windows_NT)
	CPPFLAGS += -DWIN
	BIN := tpolonen.exe
endif


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "Compiled libft objs"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "Compiled libft.a"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR):
	@/bin/mkdir -p $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; \
		then /bin/rm -rf $(OBJ_DIR); echo "Removed libft objs"; fi

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Removed libft.a"

re: fclean all

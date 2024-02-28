# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 18:18:10 by romain            #+#    #+#              #
#    Updated: 2024/02/28 16:33:46 by rdupeux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES	=	death.c \
				main.c \
				routine.c \
				utils.c \
				utils2.c \
				utils3.c
HEADER_FILES=	philo.h


HEADER_DIR	=	includes
OBJ_DIR		=	obj
SRC_DIR		=	src

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
HEADERS		= $(addprefix $(HEADER_DIR)/, $(SRC_FILES))

# Compiler, Linker Defines
CFLAGS 	= -Wall -Wextra -Werror
NAME	= philo
LIBLST	= ft_lst/liblst.a
DEBUG	= $(addsuffix _debug, $(NAME))
# Link all Object Files with external Libraries into Binaries
all: $(NAME)

re: fclean all

debug: $(DEBUG)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -g3 -I$(HEADER_DIR)/ -c -o $@ $<

$(NAME): $(OBJ) $(LIBLST)
	cc -pthread $(CFLAGS) $^ -o $@

$(DEBUG): $(OBJ) $(LIBLST)
	cc -pthread $(CFLAGS) $^ -o $@ -g3

$(LIBLST):
	make -C ft_lst

$(OBJ_DIR):
	mkdir obj

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) a.out core $(name) $(DEBUG)
	make -C ft_lst fclean 

.PHONY: all clean fclean re
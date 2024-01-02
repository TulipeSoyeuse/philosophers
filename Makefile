# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romain <romain@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 18:18:10 by romain            #+#    #+#              #
#    Updated: 2024/01/02 21:16:26 by romain           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= $(wildcard *.c)
OBJS= $(SRCS:.c=.o)

# Compiler, Linker Defines
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror
NAME	= liblst.a
LIBLST	= ft_lst/liblst.a

# Link all Object Files with external Libraries into Binaries
all: $(NAME) $(LIBLST)

re: fclean all

$(NAME): $(OBJS) $(LIBLST)
	cc -pthread $(CFLAGS) $^ -o $(NAME)

$(LIBFT):
	make -C libft

$(LIBLST):
	make -C ft_lst

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) a.out core $(name) $(DEBUG)

.PHONY: all clean fclean re
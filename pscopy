# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romain <romain@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 18:18:10 by romain            #+#    #+#              #
#    Updated: 2024/01/05 18:46:16 by romain           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= $(wildcard *.c)
OBJS= $(SRCS:.c=.o)

# Compiler, Linker Defines
CFLAGS 	= -Wall -Wextra -Werror
NAME	= philo
LIBLST	= ft_lst/liblst.a
DEBUG	= $(addsuffix _debug, $(NAME))

# Link all Object Files with external Libraries into Binaries
all: $(NAME) $(LIBLST)

re: fclean all

$(NAME): $(OBJS) $(LIBLST)
	cc -pthread $(CFLAGS) $^ -o $(NAME)

debug: $(OBJS) $(LIBLST)
	cc -pthread $(CFLAGS) $^ -o $(DEBUG) -g3

$(LIBFT):
	make -C libft

$(LIBLST):
	make -C ft_lst

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) a.out core $(name) $(DEBUG)
	make -C ft_lst fclean 

.PHONY: all clean fclean re
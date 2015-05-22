# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfournet <pfournet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by pfournet          #+#    #+#              #
#    Updated: 2015/05/22 02:29:54 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#-Wall -Wextra -Werror 
# -------------Compilateur------------------#
CC = cc
CFLAGS = -I./includes -g -O3 -Werror
#--------------Name-------------------------#
NAME = ft_ls

#--------------Sources----------------------#
FILES =	srcs/main.c	\
		srcs/libft.c	\
		srcs/libft2.c	\
		srcs/libft3.c	\
		srcs/libft4.c	\
		srcs/flags.c	\
		srcs/path.c	\
		srcs/comparisons.c	\
		srcs/comparisons2.c	\
		srcs/puts.c	\
		srcs/puts2.c	\
		srcs/puts3.c	\
		srcs/puts4.c	\
		srcs/putfiles.c \
		srcs/putfiles_debug.c \
		srcs/first_tools.c	\
		srcs/files_tools.c	\
		srcs/flags_interact.c	\
		srcs/launcher.c	\
		srcs/free.c

OBJECT = $(patsubst %.c,%.o,$(FILES))
OBJS = $(FILES:.c=.o)

#-------------------------------------------#



#--------------Actions----------------------#

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJECT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
		/bin/rm -Rf $(OBJECT)

fclean: clean
		/bin/rm -Rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
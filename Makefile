# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfournet <pfournet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by pfournet          #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by pfournet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#-Wall -Wextra -Werror 
# -------------Compilateur------------------#
CC = cc
CFLAGS = -I./includes -g -O3 -Werror
#--------------Name-------------------------#
NAME = ft_ls

#--------------Sources----------------------#
FILES =	main.c	\
		libft.c	\
		libft2.c	\
		libft3.c	\
		libft4.c	\
		flags.c	\
		path.c	\
		comparisons.c	\
		comparisons2.c	\
		puts.c	\
		first_tools.c	\
		files_tools.c	\
		flags_interact.c	\
		launcher.c	\
		free.c

OBJECT = $(patsubst %.c,%.o,$(FILES))
BASEDIR = ./srcs
#-------------------------------------------#



#--------------Actions----------------------#

all:$(NAME)

$(NAME):
		$(CC) -c $(CFLAGS) $(addprefix $(BASEDIR)/, $(FILES))
		$(CC) -o $(NAME) $(OBJECT)

clean :
		/bin/rm -Rf $(OBJECT)

fclean: clean
		/bin/rm -Rf $(NAME)

re: fclean all

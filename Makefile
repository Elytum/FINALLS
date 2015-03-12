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

# -------------Compilateur------------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -g
#--------------Name-------------------------#
NAME = ft_ls

#--------------Sources----------------------#
FILES =	main.c	\
		libft.c	\
		flags.c	\
		path.c	

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

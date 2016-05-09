# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/03 17:26:33 by snicolet          #+#    #+#              #
#    Updated: 2016/05/08 23:55:42 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
INC=-I./libft -I./headers
CFLAGS=-Wall -Wextra -Werror -Weverything -pipe
CC=clang
OBJ=main.o errors.o environement.o arguments.o envmake.o builtin.o path.o \
	envcmd.o cd.o spliter.o setenv.o unsetenv.o envdup.o help.o runcmd.o

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC)

$(NAME): libft/libft.a $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) -L ./libft -lft 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

libft/libft.a:
	make -j -C./libft

fcleanlibs: fclean
	make -C libft fclean

relibs: fcleanlibs all

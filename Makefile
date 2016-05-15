# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/03 17:26:33 by snicolet          #+#    #+#              #
#*   Updated: 2016/05/11 21:04:31 by snicolet         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME=minishell
INC=-I./libft -I./headers
CFLAGS=-Wall -Wextra -Werror -Weverything -pipe
CC=clang
OBJ=main.o errors.o environement.o arguments.o envmake.o builtin.o path.o \
	envcmd.o cd.o spliter.o setenv.o unsetenv.o envdup.o help.o runcmd.o \
	prompt.o shlvl.o buffer.o termcaps.o init.o signal.o

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC)

$(NAME): libft/libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) -L ./libft -lft -lcurses

clean:
	$(RM) $(OBJ)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

libft/libft.a:
	make -j -C./libft

.PHONY: all re clean fclean

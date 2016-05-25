# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/03 17:26:33 by snicolet          #+#    #+#              #
#    Updated: 2016/05/24 19:02:29 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
INC=-I./libft -I./headers
CFLAGS=-Wall -Wextra -Werror -Weverything -pipe
CC=clang -g3
OBJ=main.o errors.o environement.o arguments.o envmake.o builtin.o path.o \
	envcmd.o cd.o spliter.o setenv.o unsetenv.o envdup.o help.o runcmd.o \
	prompt.o shlvl.o buffer.o termcaps.o init.o signal.o export.o exit.o \
	completion.o match.o prompt2.o pwd.o envshow.o child.o termread.o \
	purgeenv.o

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

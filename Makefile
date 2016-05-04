# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/03 17:26:33 by snicolet          #+#    #+#              #
#    Updated: 2016/05/05 01:03:43 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
INC=-I./libft -I./headers
CFLAGS=-Wall -Wextra -Werror -Weverything
CC=clang
OBJ=main.o errors.o environement.o arguments.o envmake.o builtin.o

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) -L ./libft -lft 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


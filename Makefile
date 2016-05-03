# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/03 17:26:33 by snicolet          #+#    #+#              #
#    Updated: 2016/05/03 22:16:24 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
INC=-I./libft -I./headers
CFLAGS=-Wall -Wextra -Werror -Weverything
CC=clang
OBJ=main.o errors.o environement.o

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $<

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) -L ./libft -lft $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


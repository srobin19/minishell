# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srobin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 19:20:15 by srobin            #+#    #+#              #
#    Updated: 2019/10/05 01:26:05 by srobin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra
NAME = minishell
INCLUDES = minishell.h
SRCS = minishell.c path.c util.c echo.c cd.c env.c pwd.c exit.c
OBJS = minishell.o path.o util.o echo.o cd.o env.o pwd.o exit.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $^ -I. libft/libft.a -o minishell

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf $(OBJS)
	make fclean -C ./libft

fclean: clean

re: fclean all
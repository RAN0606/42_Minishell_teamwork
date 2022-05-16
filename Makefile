# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rliu <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 14:50:03 by rliu              #+#    #+#              #
#    Updated: 2022/05/16 12:52:14 by qxia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

CFLAG = -Wall -Wextra -Werror # -fPIE

IFLAGS	= -I. -I./libft

LFLAGS	= -L./libft -lft -lreadline


SRC := main.c \
	builtins/ft_pwd.c	

OBJ := $(SRC:%.c=%.o)

%.o:%.c
	$(CC) $(CFLAG) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAG) $(OBJ) $(LFLAGS) $(IFLAGS) -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C libft clean


fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean


re: fclean all

.PHONY: all clean fclean re

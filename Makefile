# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qinxia <qinxia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 14:50:03 by rliu              #+#    #+#              #
#    Updated: 2022/05/18 22:17:03 by qinxia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

CFLAG = -Wall -Wextra -Werror # -fPIE

IFLAGS	= -I. -I./libft

LFLAGS	= -L./libft -lft -lreadline


SRC := main.c \
	builtins/ft_pwd.c \
	builtins/ft_env.c \
	builtins/ft_echo.c	

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

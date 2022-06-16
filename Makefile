# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 14:50:03 by rliu              #+#    #+#              #
#    Updated: 2022/06/16 16:16:13 by qxia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

CFLAG = -Wall -Wextra -Werror # -fPIE

IFLAGS	= -I. -I./libft

LFLAGS	= -L./libft -lft -lreadline


SRC :=main.c \
	lexer_parser/lex_dollar.c \
	lexer_parser/lex_quote.c \
	lexer_parser/lex_redir.c \
	lexer_parser/lex_word.c \
	lexer_parser/lexer.c \
	lexer_parser/lex_utils.c \
	excute/ft_pipe.c \
	excute/ft_excve.c \
	builtins/ft_echo.c \
	builtins/ft_pwd.c \
	builtins/ft_cd_utils.c \
	builtins/ft_cd.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export_utils.c \
	builtins/ft_export.c \
	builtins/ft_unset.c \
	lexer_parser/ft_check_syntax.c\
	excute/par_excute.c \
	excute/ft_call_function.c \
	excute/ft_redir_in.c \
	excute/ft_redir_out.c 
#	lexer_parser/par3.c \

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

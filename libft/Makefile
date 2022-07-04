# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rliu <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 11:11:09 by rliu              #+#    #+#              #
#    Updated: 2022/05/25 15:15:58 by rliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_bzero.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_strnstr.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_memcmp.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c\
		ft_strcmp.c


BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c\


OBJS = $(SRCS:.c=.o)

OBJB = $(BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror -fPIE

NAME = libft.a

%.o:	%.c
	gcc $(FLAGS) -c $< -o $@

all: $(NAME) bonus 

bonus:      ${OBJB} ${OBJS}
		ar rcs ${NAME} ${OBJS} ${OBJB}

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		rm -f $(OBJS) $(OBJB)

fclean:	clean
		rm -f $(NAME)

re:	fclean $(NAME)

.PHONY:     all fclean clean re bonus

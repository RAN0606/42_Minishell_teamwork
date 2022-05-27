/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/05/27 18:58:06 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

# define BUFFER_SIZE 10000

enum token {L_WORD, L_PIPE, L_INPUT, L_OUTPUT, L_APPEND, L_HEREDOC};

typedef struct s_token
{
	int	token;
	char	*str;
	int	id;
}t_token;

typedef struct s_word
{
	char	*str;
	char	*ptr_cmd;
	int	nb;
}t_word;

struct g_ms_info
{
	char	**env_tab;
	t_list	*token_list;
};

/*******************Env********************/

//****env_utils.c*********

int ft_check_envvalue(char *keyequal, char **envtab);
char *ft_return_envvalue(char *key, char **envtab);

/******************* Lexer + Parser *******************/

//*****lp_utils.c

char	*ft_strjoinfree(char *s1, char *s2);



t_list	*ft_lexer(char *cmd, char **envtab);

void ft_free_token (void *token);

int	ft_pwd(void);

#endif

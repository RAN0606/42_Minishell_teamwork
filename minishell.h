/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/05/25 15:14:13 by rliu             ###   ########.fr       */
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
	int	nb;
}t_word;

struct g_ms_info
{
	char	**env_tab;
	t_list	*token_list;
};

t_list	*ft_lexer(char *cmd, char **envtab);

int	ft_pwd(void);

#endif

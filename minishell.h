/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/05/24 12:16:50 by qxia             ###   ########.fr       */
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

# define BUFFER_SIZE 4096

typedef struct  s_token
{
    int id;
    char    *value;
}t_token;

typedef struct  s_env
{
    char    *value;
    struct s_env    *next;    
}t_env;

typedef struct  s_mini
{
    t_env   *env;
    t_token *start;

}t_mini;

int	ft_pwd(void);
char	**ft_getenv(char **env);
void ft_env(char **envtab);
void 	ft_free_env(char **envtab);
int	ft_echo(char **args);

#endif

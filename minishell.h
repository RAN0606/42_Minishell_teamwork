/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/05/31 15:12:29 by qxia             ###   ########.fr       */
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

typedef struct  s_data
{
    char    **env;
    char    *pwd;
    int     fd_in;
    int     fd_out;
    int     redir;
}t_data;

//int	g_status;
int	ft_pwd(void);
int	ft_envlen(char **env);
char	**ft_getenv(char **env);
void	ft_env(char **envtab);
void	ft_free_env(char **envtab);
int	ft_echo(char **args);
void	change_env_pwd(t_data *data);
void	change_env_oldpwd(t_data    *data);
int	change_pwd(t_data *data, char *input);
int	cd_only(t_data *data);
int	cd_path(char **args, t_data *data);
void	ft_cd(char **args, t_data *data);
//void	error_message(char  *str, int status);
int	ft_index(char   *name, t_data *data);
void	change_var(char *new_var, t_data *data, int index);
char	**export_env(char    **old_env, char *export);
int	check_export(char *str);
void    print_export(char **env);

#endif

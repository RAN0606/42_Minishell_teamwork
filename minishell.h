/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/06/16 16:06:15 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "libft/libft.h"

#	define BUFFER_SIZE 1
enum token {L_WORD = 1, L_PIPE, L_INPUT, L_OUTPUT, L_APPEND, L_HEREDOC};

typedef struct s_token
{
	int		token;
	char	*str;
	int		is_save;
}t_token;

typedef struct s_word
{
	char	*str;
	char	*ptr_cmd;
	int		nb;
}t_word;

/*typedef struct s_count_token
{
	int		nb_word;
	int		nb_redir_in;
	int		nb_redir_out;
	int		nb_redir_hd;
	int		nb_redir_apd;
}t_count_token;

typedef struct s_cmdtab
{
	t_list	*word_list;
	t_list	*redir_in_list;
	t_list	*redir_out_list;
	t_list	is_pipe;
}t_cmdtab;*/

struct g_ms_info
{
	char	**env_tab;
	t_list	*lex_list;
	t_list  *cmd_tab_list;
};

//two structures below are from qin_branch_builtins 
typedef struct  s_data
{
    char    **env;
    char    *pwd;
    int     fd_in;
    int     fd_out;
    int     redir;
}       t_data;

typedef struct s_cmd  //just copy xue's
{
	char	**cmd;
	t_list	*in_streams;
	t_list	*in_stream_head;
	t_list	*out_streams;
	t_list	*out_streams_head;
	int		flag;
	int		dlr;
}		t_cmd;


/*******************Env********************/

//****env_utils.c*********

int ft_check_envvalue(char *keyequal, char **envtab);
char *ft_return_envvalue(char *key, char **envtab);

/******************* Lexer + Parser *******************/

int ft_check_envvalue(char *keyequal, char **envtab);
int ft_check_envkey(char *cmd);

/************lexer.c******************/
t_list	*ft_lexer(char *cmd, char **envtab);

/*****lex_utils.c*/
char	*ft_strjoinfree(char *s1, char *s2);
void	ft_print_token(void *token);
void ft_free_token (void *token);
t_list *ft_token(int token, char *str);
int	ft_add_token_element(t_list **token_list, int token, char *str);
/*******lex_dollar.c*/
char *ft_return_envvalue(char *key, char **envtab);
char	*ft_dollar_inword(char *temp_cmd, char **envtab, t_word *word);
char	*ft_handle_dollar(char *cmd, char **envtab);
/********lex_quote.c*/
int	ft_chr_quote(char *cmd, char c);
char	*ft_return_quotevalue(char *cmd, char c, char **envtab,int j);
char *ft_handle_quote (char *temp_cmd, t_word *word, char **envtab);
/*******lex_word.c*/
int	ft_check_signe(char c);
t_word	*ft_readword(char *temp_cmd, char **envtab);
char	*ft_add_word(char *cmd, t_list **token_list, char **envtab);
/*******lex_redir.c*/
char	*ft_handle_redir(char *cmd, t_list **token_list);
/*******ft_check_syntax.c*/
int	ft_check_syntax(t_list *lex_list);
/********par_excute************************/
int	ft_simplecmd(t_list *lex_list, char **envtab);
int		ft_parser_cmd(t_list *lex_list,char **envtab);
int	ft_excute_simplecmd(t_list *lex_list, char **envtab);
/****ft_excve.c***/
int	ft_excuvp(char **simplecmd, char **envtab);

/****ft_call_function.c*/
int ft_call_function(char **cmdtab, char **envtab);

int		ft_redir_in(t_list *lex_list, char *name);

char *ft_tmpname(void);
int		ft_redir_out(t_list *lex_list);

int ft_pipe(t_list *lex_list, char **envtab);
/***************************builtin*********************/
int	ft_pwd(void);
int     ft_echo(char **args);
char	*get_next_line(int fd);
int	ft_envlen(char **env);
char	**ft_getenv(char **env);
void	ft_env(char **envtab);
void	ft_free_env(char **envtab);
void	change_env_pwd(t_data *data);
void	change_env_oldpwd(t_data    *data);
int	change_pwd(t_data *data, char *input);
int	cd_only(t_data *data);
int	cd_path(char **args, t_data *data);
void	ft_cd(char **args, t_data *data);
int	ft_index(char   *name, t_data *data);
void	change_var(char *new_var, t_data *data, int index);
char	**export_env(char    **old_env, char *export);
int	check_export(char *str);
void    print_export(char **env);
void    ft_exit(t_cmd   *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/07/19 15:53:22 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define BUFFER_SIZE 4096
# define NAME_MAX	255
# define L_WORD		1
# define L_PIPE		2
# define L_INPUT	3
# define L_OUTPUT	4
# define L_APPEND 	5
# define L_HEREDOC	6

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
typedef struct s_data
{
	char	**env;
	char	*pwd;
	t_list	*token_list;
}t_data;

typedef struct ms
{
	t_data	*data;
	char	*hd_name;
	int		status;
}t_ms;

extern t_ms	g_ms;
/*******************Env********************/
void	ft_handler(int sigu);
int		ft_check_envvalue(char *keyequal, char **envtab);
char	*ft_return_envvalue(char *key, char **envtab);

/******************* Lexer + Parser *******************/

int		ft_check_envvalue(char *keyequal, char **envtab);
int		ft_check_envkey(char *cmd);

/************lexer.c******************/
t_list	*ft_lexer(char *cmd, char **envtab);

/*****lex_utils.c*/
char	*ft_strjoinfree(char *s1, char *s2);
void	ft_print_token(void *token);
void	ft_free_token(void *token);
t_list	*ft_token(int token, char *str);
int		ft_add_token_element(t_list **token_list, int token, char *str);
/*******lex_dollar.c*/
char	*ft_return_envvalue(char *key, char **envtab);
char	*ft_dollar_inword(char *temp_cmd, char **envtab, t_word *word);
char	*ft_handle_dollar(char *cmd, char **envtab);
/********lex_quote.c*/
int		ft_chr_quote(char *cmd, char c);
char	*ft_return_quotevalue(char *cmd, char c, char **envtab, int j);
char	*ft_handle_quote(char *temp_cmd, t_word *word, char **envtab);
/*******lex_word.c*/
int		ft_check_signe(char c);
t_word	*ft_readword(char *temp_cmd, char **envtab);
char	*ft_add_word(char *cmd, t_list **token_list, char **envtab);
/*******lex_redir.c*/
char	*ft_handle_redir(char *cmd, t_list **token_list);
/*******ft_check_syntax.c*/
int		ft_check_syntax(t_data *data);
void	ft_free_heredoc(void);
/*******edoc.c*/
char	*ft_tmpname(void);
int		ft_heredoc(t_list *list_ptr, char *name, t_data *data);
/********par_excute************************/
/****ft_excute_utiles.c***/
int		ft_perror(char *str, int i);
/****par_excve.c***/
char	*ft_tmpname(void);
char	**ft_save_simple_cmd(t_list *lex_list);
t_list	*ft_next_pipecmd(t_list *lex_list);
int		ft_simplecmd(t_data *data);
int		ft_parser_cmd(t_data *data);
int		ft_excute_simplecmd(t_list *lex_list, char **envtab, t_data *data);
/****ft_excve.c***/
int		ft_excuvp(char **simplecmd, char **envtab);

/****ft_call_function.c*/
int		ft_call_function(char **cmdtab, t_data *data);
int		ft_redir_in(t_list *lex_list);
char	*ft_tmpname(void);
int		ft_redir_out(t_list *lex_list);

int		ft_pipe(t_list *lex_list, t_data *data);
/***************************builtin*********************/
int		ft_pwd(void);
int		ft_echo(char **args);
char	*get_next_line(int fd);
int		ft_envlen(char **env);
char	**ft_getenv(char **env);
int		ft_env(t_data *data);
void	ft_free_env(char **envtab);
void	change_env_pwd(t_data *data);
void	change_env_oldpwd(t_data *data);
int		change_pwd(t_data *data, char *input);
int		cd_only(t_data *data);
int		cd_path(char **args, t_data *data);
int		ft_cd(char **args, t_data *data);
int		ft_index(char *name, t_data *data);
void	change_var(char *new_var, t_data *data, int index);
char	**export_env(char **old_env, char *export);
int		check_export(char *str);
void	print_export(char **env);
int		ft_export(char **list_cmd, t_data *data);
int		ft_exit(char **cmd, t_data *data);
int		ft_unset(char **list_cmd, t_data *data);
void	ft_pipe_call_function(char **cmdtab, t_data *data);
int		ft_pipe_simplecmd(t_list *lex_list, t_data *data);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/06/03 19:26:32 by rliu             ###   ########.fr       */
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
/********parser.c***********************/

void parser_cmd(t_list *lex_list);


/***************************builtin*********************/
int	ft_pwd(void);
int     ft_echo(char **args);

#endif

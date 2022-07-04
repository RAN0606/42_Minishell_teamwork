/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_excute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/04 17:16:56 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_count_simple_cmd(t_list *lex_list)
{
	int		size;
	t_list	*list_ptr;
	
	size = 0;
	list_ptr = lex_list;
	while (list_ptr && ((t_token *)(list_ptr->content))->token != L_PIPE)
	{
		if (((t_token *)(list_ptr->content))->token != L_WORD)
			list_ptr = list_ptr->next;
		else if (((t_token *)(list_ptr->content))->token == L_WORD)
			size++;
		list_ptr = list_ptr->next;
	}
	return (size);
}

char	**ft_save_simple_cmd(t_list *lex_list)
{
	int		size;
	int		i;
	char	**list_cmd;
	t_list	*list_ptr;
	
	size = ft_count_simple_cmd(lex_list);
	list_cmd = (char **)ft_calloc(size+1, sizeof(char *));
	if (!list_cmd)
		return NULL;
	i = -1;
	list_ptr = lex_list;
	while (list_ptr && ((t_token *)(list_ptr->content))->token != L_PIPE)
	{
		if (((t_token *)(list_ptr->content))->token != L_WORD)
			list_ptr = list_ptr->next;
		else if (((t_token *)(list_ptr->content))->token == L_WORD)
			list_cmd[++i] = ft_strdup(((t_token *)(list_ptr->content))->str);
		list_ptr = list_ptr->next;
	}
	return (list_cmd);
}

int	ft_simplecmd(t_list *lex_list, char **envtab, t_data *data)
{
	char	**simple_cmd;
	int		oldfd[2];
	int		code;
	
	code = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	ft_redir_in (lex_list);
	ft_redir_out(lex_list);
	simple_cmd = ft_save_simple_cmd(lex_list);
	code = ft_call_function(simple_cmd, envtab, data);
	ft_free_env(simple_cmd);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close(oldfd[0]);
	close(oldfd[1]);
	return (code);
}

int	ft_pipe_simplecmd(t_list *lex_list, char **envtab, t_data *data)
{
	char	**simple_cmd;

	ft_redir_in(lex_list);
	ft_redir_out(lex_list);
	simple_cmd = ft_save_simple_cmd(lex_list);
	ft_pipe_call_function(simple_cmd, envtab, data);
	return (0);
}

int	ft_excute_simplecmd(t_list *lex_list, char **envtab, t_data *data)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
		ft_simplecmd(lex_list, envtab, data);
    else if (pid < 0)
        exit(EXIT_FAILURE);
    else
	{
		if (waitpid(pid, &status, 0) != pid)
			exit(EXIT_FAILURE);
	}
	return (0);
}
	
t_list *ft_next_pipecmd(t_list *lex_list)
{
	int		token;
	t_list  *list_ptr;
	
	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		list_ptr = list_ptr->next;
		if (token == L_PIPE)
			return (list_ptr);
	}
	return (NULL);
}

int ft_parser_cmd(t_list *lex_list, char **envtab, t_data *data)
{
	t_list  *list_ptr;
	t_list	*next_cmd;
	int 	code;

	list_ptr = lex_list;
	if (ft_check_syntax(lex_list))
		return (-1);
	next_cmd = ft_next_pipecmd(list_ptr);
	if (next_cmd)
		code = ft_pipe(lex_list, data);
	else if (list_ptr)
		code = ft_simplecmd(lex_list, envtab, data);
	g_status = code;
	return (code);
}


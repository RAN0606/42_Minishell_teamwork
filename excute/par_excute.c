/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_excute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/15 18:35:55 by rliu             ###   ########.fr       */
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
			list_cmd[++i] = ((t_token *)(list_ptr->content))->str;
		list_ptr = list_ptr->next;
	}
	return (list_cmd);
}
int	ft_simplecmd(t_list *lex_list, char **envtab)
{
	char	**simple_cmd;
	char	*name;

	name = ft_tmpname();
	if(ft_redir_in(lex_list,name))
		return (-1);
	ft_redir_out(lex_list);
	simple_cmd = ft_save_simple_cmd(lex_list);
	ft_call_function(simple_cmd, envtab);
	free(simple_cmd);
	unlink(name);
	free (name);
	return (0);
}

int	ft_excute_simplecmd(t_list *lex_list, char **envtab)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
		ft_simplecmd(lex_list, envtab);
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

int ft_parser_cmd(t_list *lex_list, char **envtab)
{
	t_list  *list_ptr;
	t_list	*next_cmd;
	int		stdfd;

	list_ptr = lex_list;
	if (ft_check_syntax(lex_list))
		return (-1);
	stdfd = dup(0);
	while (list_ptr)
	{
		next_cmd = ft_next_pipecmd(list_ptr);
		if (next_cmd)
			ft_pipe(list_ptr, envtab);
		else
			ft_excute_simplecmd(list_ptr, envtab);			
		list_ptr = next_cmd;
	}
	dup2(stdfd, 0);
	close(stdfd);
	return (0);
}

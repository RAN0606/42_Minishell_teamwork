/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/13 19:57:56 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_syntax(t_list *lex_list)
{
	t_list	*list_ptr;
	int		last_token;
	
	last_token = 0;
	list_ptr = lex_list;
	while (list_ptr)
	{
        if (last_token == 0 && ((t_token *)(list_ptr->content))->token == L_PIPE)
        {
			printf("minish: syntax error near unexpected token `|'\n");
			return (1);
		}
		else if (last_token > L_WORD && 
			(((t_token *)(list_ptr->content))->token > L_WORD))
		{
			printf("minish: syntax error near unexpected token `%s'\n", ((t_token *)(list_ptr->content))->str);
			return (1);
		}
		last_token = ((t_token *)(list_ptr->content))->token;
		list_ptr = list_ptr->next;
	}
	if (last_token > L_WORD)
	{
			printf("minish: syntax error near unexpected token `newline'\n");
			return (1);
	}
	return (0);
}

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

t_list	*ft_find_piple(t_list *lex_list)
{
	t_list	*list_ptr;
	
	list_ptr = lex_list;
	while (list_ptr)
	{
		if (((t_token *)(list_ptr->content))->token != L_PIPE)
			return (list_ptr);
		list_ptr = list_ptr->next;
	}
	return (0);
}

int		ft_call_builtin(char **list_cmd)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
		return (ft_echo(list_cmd));
	return (-1);
}

int		ft_call_function(char **list_cmd)
{
	int code;
	
	code = -1;
	code = ft_call_builtin(list_cmd);
	if (code >= 0)
		return (code);
	return (127);
}

int ft_input(t_list *lex_list)
{
	int		fd;
	char	*path;
	int		code;
//	char	buf[1024];

	code = 0;
	if (lex_list)
	{
		path = ((t_token *)(lex_list->content))->str;
		fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", path);
			return (-1);
		}
		else
		{
			code = dup2(fd, 0);
			close(fd);
//			read(0, buf, 10);
//			printf("test%s",buf);
			return (code);
		}
	}
	return (0);
}

char *ft_filename(void)
{
	static char	name[256];
	static int	i;
	static int	c = 48;

	if (c== 123)
	{
		c = 48;
		i++;
	}
	name[i] = c;
	c++;
	return (ft_strdup(name));
}

char *ft_tmpname(void)
{
	char *name;

	name = ft_filename();
	while (!access(name,F_OK))
	{
		free(name);
		name = ft_filename();
	}
	if (!name)
		return(0);
	return (name);
}

int ft_heredoc(t_list *lex_list, char *name)
{
	char	*str;
	char	*line;
	int		fd;

	str = ((t_token *)(lex_list->content))->str;
	fd = open(name, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	if (!name || fd < 0)
		return (-1);
	line = readline(">");
	while (ft_strcmp(line, str) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline(">");
	}
	close (fd);
	fd = open (name, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int		ft_redir_in(t_list *lex_list, char *name)
{
	int		token;
	t_list	*list_ptr;

	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			return (0);
		else if (token == L_INPUT)
		{
			list_ptr = list_ptr->next;
			if (ft_input(list_ptr) == 2)
				return (2);
		}
		else if (token == L_HEREDOC)
		{	
			list_ptr = list_ptr->next;
			if (ft_heredoc(list_ptr, name))
				return (3);
		}
			list_ptr = list_ptr->next;
	}
	return (0);
}
int		ft_output(t_list *lex_list)
{
	char *name;
	int	 fd;

	name = ((t_token *)(lex_list->content))->str;
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd <0)
		return (-1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		ft_append(t_list *lex_list)
{
	char *name;
	int	 fd;

	name = ((t_token *)(lex_list->content))->str;
	fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		return (-1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		ft_redir_out(t_list *lex_list)
{
	int		token;
	t_list  *list_ptr;
	
	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			return (0);
		else if (token == L_OUTPUT)
		{
			list_ptr = list_ptr->next;
			if (ft_output(list_ptr) < 0)
				return (-1);
		}
		else if (token == L_APPEND)
		{	
			list_ptr = list_ptr->next;
			if (ft_append(list_ptr) < 0)
				return (-1);
		}
		
		list_ptr = list_ptr->next;
	}
	return (0);
}

int	ft_excute_simplecmd(t_list *lex_list, char **envtab)
{
	char	**simple_cmd;
	char	*name;
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	name = ft_tmpname();
	if(ft_redir_in(lex_list,name))
		return (-1);
	ft_redir_out(lex_list);
	simple_cmd = ft_save_simple_cmd(lex_list);
//	ft_call_builtin(simple_cmd, envtab);
	ft_call_execve(simple_cmd, envtab);
	free(simple_cmd);
	unlink(name);
	free (name);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	return (0);
}

t_list *ft_next_pipe(t_list *lex_list)
{
	int		token;
	t_list  *list_ptr;
	
	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			return (list_ptr);
		list_ptr = list_ptr->next;
	}
	return (NULL);
}
/* wait pipe
int ft_parser_cmd(t_list *lex_list, char **envtab)
{
	t_list  *list_ptr;
	int		fd[2];
	int		pid;
	int 	signal;

	list_ptr = lex_list;
	if (ft_check_syntax(lex_list))
		return (-1);
	while (list_ptr)
	{
		ft_excute_simplecmd(list_ptr, envtab);
		list_ptr = ft_next_pipe(list_ptr);
		if (list_ptr)
		{
			ft_pipe();
	}
	return (0);
}*/ 
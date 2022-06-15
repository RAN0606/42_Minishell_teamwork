/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/15 18:21:09 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


int ft_input(t_list *lex_list)
{
	int		fd;
	char	*path;
	int		code;

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

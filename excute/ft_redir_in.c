/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/12 16:17:14 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


int ft_input(t_list *lex_list)
{
	char	*path;

	if (lex_list)
	{
		path = ((t_token *)(lex_list->content))->str;
		if (access(path, F_OK) != 0)
		{
			printf("%s: No such file or directory\n", path);
			return (1);
		}
	}
	return (0);
}

/*char *ft_filename(void)
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

void ft_hadler_heredoc(int sigu)
{
	if (sigu == SIGINT)
	{		
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

int ft_heredoc(t_list *lex_list, char *name)
{
	char	*str;
	char	*line;
	int		fd[2];
	int 	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
	str = ((t_token *)(lex_list->content))->str;
	//str = ft_strjoinfree(ft_strdup(str), ft_strdup("\n"));
	fd[0] = open(name, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	if (!name || fd[0] < 0)
		exit (1);
	line = NULL;
	while (1)
	{	
		signal(SIGINT, SIG_DFL);
		line = readline(">");
		if (!line)
		{
			ft_perror("Warning: heredocument is ended by end-of-file\n");
			break ;
		}			
		if (ft_strcmp(line, str) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd[0]);
		ft_putstr_fd("\n", fd[0]);
		free(line);
	}
		exit (0);
	}
	else
	{	
		waitpid(pid, &status, 0);
		g_status=WEXITSTATUS(status);
	//	printf("test %d", g_status);
		return (g_status);
	}
	return (0);
}*/

int		ft_redir_in(t_list *lex_list)
{
	int		token;
	t_list	*list_ptr;
	int		fd;
	char	*lastin_name;

	lastin_name = 0;
	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			break;
		else if (token == L_INPUT)
		{
			list_ptr = list_ptr->next;
			if (ft_input(list_ptr) == 2)
				return (2);
			lastin_name = ((t_token *)(list_ptr->content))->str;
		}
		else if (token == L_HEREDOC)
		{
			list_ptr = list_ptr->next;
			lastin_name = ((t_token *)(list_ptr->content))->str;
		}
		list_ptr = list_ptr->next;
	}
	if (lastin_name != 0)
	{
		fd = open(lastin_name, O_RDONLY);
		if (fd < 0)
		{
			perror("fd:");
			return (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

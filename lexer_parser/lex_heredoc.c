/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/19 16:23:57 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_filename(void)
{
	static char	name[256];
	static int	i;
	static int	c = 48;

	if (c == 123)
	{
		c = 48;
		i++;
	}
	name[i] = c;
	c++;
	return (ft_strdup(name));
}

char	*ft_tmpname(void)
{
	char	*name;

	name = ft_filename();
	while (!access(name, F_OK))
	{
		free(name);
		name = ft_filename();
	}
	if (!name)
		return (0);
	return (name);
}

void	ft_hadler_heredoc(int sigu)
{
	if (sigu == SIGINT)
	{		
		ft_putstr_fd("\n", 0);
		ft_free_heredoc();
		exit(130);
	}
}

void	ft_heredoc_readline(int fd, char *str, t_data *data)
{
	char	*line;

	while (1)
	{
		g_ms.data = data;
		signal(SIGINT, ft_hadler_heredoc);
		line = readline(">");
		if (!line)
		{
			ft_perror("Warning: heredocument is ended by end-of-file\n", 0);
			break ;
		}
		if (ft_strcmp(line, str) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	ft_free_heredoc();
	exit (0);
}

int	ft_heredoc(t_list *list_ptr, char *name, t_data *data)
{
	char	*str;
	int		fd;
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		str = ((t_token *)(list_ptr->content))->str;
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (!name || fd < 0)
			exit (1);
		g_ms.hd_name = name;
		ft_heredoc_readline(fd, str, data);
	}
	else
	{	
		waitpid(pid, &status, 0);
		g_ms.status = WEXITSTATUS(status);
		return (g_ms.status);
	}
	return (0);
}

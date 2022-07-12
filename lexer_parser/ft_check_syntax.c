/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/12 16:08:12 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


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

void ft_hadler_heredoc(int sigu)
{
	if (sigu == SIGINT/* && EINTR == errno*/)
	{		
		ft_putstr_fd("\n", 0);
		g_status = 130;
		exit(130);
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
		signal(SIGINT, ft_hadler_heredoc);
		line = readline(">");
		if (!line)
		{
			ft_perror("Warning: heredocument is ended by end-of-file\n");
			break ;
		}			
		if (ft_strcmp(line, str) == 0)
		{
	//		printf("test1 line: %s str: %s", line, str);
			free(line);
			break;
		}	
	//	printf("test2 line: %s str: %s", line, str);
		ft_putstr_fd(line, fd[0]);
		ft_putstr_fd("\n", fd[0]);
		free(line);
	}
		close(fd[0]);
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
}
int ft_save_heredoc (t_list *lex_list)
{
	t_list	*list_ptr;
	int		token;
	int		code;
	char	*name;
	
	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_HEREDOC)
		{
			list_ptr = list_ptr->next;	
			name = ft_tmpname();
			code = ft_heredoc(list_ptr, name);
			if (code != 0)
			{
				unlink(name);
				free(name);
				return (130);
			}
			else
			{
				free(((t_token *)(list_ptr->content))->str);
				((t_token *)(list_ptr->content))->str = name;
				((t_token *)(list_ptr->content))->is_save = 1;
			}
		}
		list_ptr = list_ptr->next;	
	}
	return (0);
}

int ft_p_syntaxerr(int nb, char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (nb);
}
int	ft_check_syntax(t_list *lex_list)
{
	t_list	*list_ptr;
	int		last_token;

	last_token = 0;
	list_ptr = lex_list;
	while (list_ptr)
	{
        if (last_token == 0 && ((t_token *)(list_ptr->content))->token == L_PIPE)
			return (ft_p_syntaxerr(1, "syntax er`|'\n"));
		else if (last_token > L_WORD && 
			(((t_token *)(list_ptr->content))->token > L_WORD))
			return (ft_p_syntaxerr(1, ((t_token *)(list_ptr->content))->str));
		last_token = ((t_token *)(list_ptr->content))->token;
		list_ptr = list_ptr->next;
	}
	if (last_token > L_WORD)
			return (ft_p_syntaxerr(1, "newline"));
	if(ft_save_heredoc(lex_list) != 0)		
		return (130);
	return (0);
}

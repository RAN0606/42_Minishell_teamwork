/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:02:00 by qxia              #+#    #+#             */
/*   Updated: 2022/07/13 11:56:10 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_cmd(int pid, t_list *lex_list, t_data *data, int *fd)
{
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_pipe_simplecmd(lex_list, data->env, data);
		if (data->token_list)
			ft_lstclear(&(data->token_list), ft_free_token);
		exit(EXIT_SUCCESS);
	}
}

void	second_cmd(int pid, t_list *lex_list, t_data *data, int *fd)
{
	t_list	*pipecmd;

	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		pipecmd = ft_next_pipecmd(lex_list);
		if (pipecmd)
			ft_pipe(lex_list, data);
		else
			ft_pipe_simplecmd(lex_list, data->env, data);
		ft_lstclear(((&data->token_list)), ft_free_token);
		ft_free_env(data->env);
		free(data->pwd);
		exit(EXIT_SUCCESS);
	}
}

int	ft_pipe_simplecmd(t_list *lex_list, char **envtab, t_data *data)
{
	char	**simple_cmd;

	if (ft_redir_in(lex_list))
		return (130);
	ft_redir_out(lex_list);
	simple_cmd = ft_save_simple_cmd(lex_list);
	ft_pipe_call_function(simple_cmd, envtab, data);
	ft_free_env(simple_cmd);
	return (0);
}

t_list	*ft_next_pipecmd(t_list *lex_list)
{
	int		token;
	t_list	*list_ptr;

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

int	ft_pipe(t_list *lex_list, t_data *data)
{
	int		pid[2];
	int		fd[2];
	int		status[2];
	t_list	*pipecmd;
	t_list	*list_ptr;

	list_ptr = lex_list;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pipecmd = ft_next_pipecmd(list_ptr);
	if (pipecmd)
	{
		pid[0] = fork();
		first_cmd(pid[0], list_ptr, data, fd);
		pid[1] = fork();
		second_cmd(pid[1], pipecmd, data, fd);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	g_status = WEXITSTATUS(status[1]);
	return (g_status);
}

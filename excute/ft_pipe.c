/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:02:00 by qxia              #+#    #+#             */
/*   Updated: 2022/06/27 13:13:11 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int ft_pipe(t_list *lex_list, char **envtab, t_data *data)
{
    pid_t   pid;
    int     fd[2];
	int		status;
	int		oldfd[2];
    
	if (pipe(fd) == -1)
        exit(EXIT_FAILURE);
    pid = fork();
    if (pid == 0)
    {
        usleep(100);
		dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
		ft_pipe_simplecmd(lex_list, envtab, data);
    }
    else if (pid < 0)
        exit(EXIT_FAILURE);
    else
	{
		oldfd[0] = dup(0);
		oldfd[1] = dup(1);
		if (waitpid(pid, &status, 0) != pid)
			exit(EXIT_FAILURE);
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(oldfd[1], 1);
		close(fd[0]);
	}
    return (1);
}*/
void		first_cmd(int pid, t_list *lex_list, t_data *data, int *fd)
{
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_pipe_simplecmd(lex_list, data->env, data);
		exit(EXIT_SUCCESS);
	}
}

void	second_cmd(int pid, t_list *lex_list, t_data *data, int *fd)
{
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_pipe(lex_list, data);
		exit(EXIT_SUCCESS);
	}
}
int ft_pipe(t_list *lex_list , t_data *data)
{
	int pid[2];
	int fd[2];
	int	status[2];
	t_list *pipecmd;
	t_list *list_ptr;
		
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
	else
		ft_pipe_simplecmd(list_ptr, data->env, data);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	g_status = WEXITSTATUS(status[1]);
	return (g_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:02:00 by qxia              #+#    #+#             */
/*   Updated: 2022/06/17 17:45:59 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pipe(t_list *lex_list, char **envtab)
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
		ft_simplecmd(lex_list, envtab);
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
}

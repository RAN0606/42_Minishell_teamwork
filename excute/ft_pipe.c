/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:02:00 by qxia              #+#    #+#             */
/*   Updated: 2022/06/15 17:55:10 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pipe(t_list *lex_list, char **envtab)
{
    pid_t   pid;
    int     fd[2];
	int		status;
    
	if (pipe(fd) == -1)
        exit(EXIT_FAILURE);
    pid = fork();
    if (pid == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
		ft_simplecmd(lex_list, envtab);
    }
    else if (pid < 0)
        exit(EXIT_FAILURE);
    else
	{
		if (waitpid(pid, &status, 0) != pid)
			exit(EXIT_FAILURE);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
    return (1);
}

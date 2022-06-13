/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:57:50 by rliu              #+#    #+#             */
/*   Updated: 2022/06/13 17:11:36 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_excuvp(char **simplecmd, char **envtab)
{
	char *path;
	char **pathlist;
	char **temp;
	char *cmdpath;

	path = ft_return_envvalue("PATH", envtab);
	pathlist = ft_split(path, ':');
	temp = pathlist - 1;
	cmdpath = ft_strjoinfree(ft_strdup("/"), ft_strdup(*simplecmd));
	while (*(++temp))
		*temp = ft_strjoinfree(*temp, ft_strdup(cmdpath));
	free(cmdpath);
	temp = pathlist - 1;
	while (*(++temp))
		execve(*temp, simplecmd, NULL);
	return (-1);
}

int ft_call_execve(char **simplecmd, char **envtab)
{
	int pid;
	int signal;

	pid = fork();
	if (pid == 0)
	{
		if(ft_excuvp(simplecmd, envtab)==-1)
		{
			printf("cmd not found\n");
			exit(126);
		}
	}
	else
	{
		waitpid(pid, &signal, 0);
		signal = WEXITSTATUS(signal);
		if (signal == 13)
			signal = 126;
	}
	return (signal);
}

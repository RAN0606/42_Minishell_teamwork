/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/27 14:49:51 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		ft_call_builtin(char **list_cmd, t_data *data)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
		return(ft_echo(list_cmd));
	else if (!ft_strcmp(list_cmd[0], "pwd"))
		return(ft_pwd());
	else if (!ft_strcmp(list_cmd[0], "cd"))
		return(ft_cd(list_cmd, data));
	else if (!ft_strcmp(list_cmd[0], "env"))
		return(ft_env(data));
	else if (!ft_strcmp(list_cmd[0], "exit"))
		ft_exit(list_cmd);
	else if (!ft_strcmp(list_cmd[0], "export"))
		return(ft_export(list_cmd, data));
	else if (!ft_strcmp(list_cmd[0], "unset"))
		return(ft_unset(list_cmd, data));
	/*else
	{
		ft_exec(list_cmd, data);
	}*/
	return (-1);
}

void	ft_perror(char *str)
{
	int len;

	len = ft_strlen(str);
	write(2, str, len + 1);
}
int 	ft_call_excuve(char **cmdtab, t_data *data)
{
	int pid;
	int status;
	
	pid =  fork();
	
	if (pid < 0)
	{
		perror("fork fail");
		return (1);
	}
	if (pid == 0)
	{
		if(ft_excuvp(cmdtab, data->env)==-1)
		{
			
			ft_perror("cmd not fount\n");
			exit(127);
		}
	}
	else 
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(1);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	ft_call_function(char **cmdtab, char **envtab, t_data *data)
{
	int code;

	(void)envtab;
	code = ft_call_builtin(cmdtab, data);
	if (code == -1)
		return (ft_call_excuve(cmdtab, data));
	return (code);
}

void ft_pipe_call_function(char **cmdtab, char **envtab, t_data *data)
{
	int code;

	(void)envtab;
	code = ft_call_builtin(cmdtab, data);
	if (code == -1)
	{
		if (ft_excuvp(cmdtab, data->env)==-1)
		{
			ft_perror("cmd not found\n");
			exit (127);
		}
	}
	exit (code);
}

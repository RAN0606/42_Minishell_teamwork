/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/19 15:40:38 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_call_builtin(char **list_cmd, t_data *data)
{
	if (ft_strcmp(list_cmd[0], "echo") == 0)
		return (ft_echo(list_cmd));
	else if (!ft_strcmp(list_cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(list_cmd[0], "cd"))
		return (ft_cd(list_cmd, data));
	else if (!ft_strcmp(list_cmd[0], "env"))
		return (ft_env(data));
	else if (!ft_strcmp(list_cmd[0], "exit"))
		return (ft_exit(list_cmd, data));
	else if (!ft_strcmp(list_cmd[0], "export"))
		return (ft_export(list_cmd, data));
	else if (!ft_strcmp(list_cmd[0], "unset"))
		return (ft_unset(list_cmd, data));
	return (-1);
}

void	ft_excuve_free(t_data *data, char **cmdtab)
{
	ft_perror("cmd is not found\n", 0);
	free(data->pwd);
	ft_free_env(data->env);
	ft_free_env(cmdtab);
	ft_lstclear(&(data->token_list), ft_free_token);
	exit(127);
}

int	ft_call_excuve(char **cmdtab, t_data *data)
{
	int	pid;
	int	status;
	int	code;

	pid = fork();
	if (pid < 0)
	{
		perror("fork fail");
		return (1);
	}
	if (pid == 0)
	{
		if (ft_excuvp(cmdtab, data->env) == -1)
			ft_excuve_free(data, cmdtab);
	}
	if (waitpid(pid, &status, 0) == -1)
		exit(1);
	code = WIFEXITED(status);
	if (!code)
		return (127);
	return (WEXITSTATUS(status));
}

int	ft_call_function(char **cmdtab, t_data *data)
{
	int	code;

	code = ft_call_builtin(cmdtab, data);
	if (code == -1)
		return (ft_call_excuve(cmdtab, data));
	return (code);
}

void	ft_pipe_call_function(char **cmdtab, t_data *data)
{
	int	code;

	code = ft_call_builtin(cmdtab, data);
	if (code == -1)
	{
		if (ft_excuvp(cmdtab, data->env) == -1)
		{
			ft_perror("cmd not found\n", 0);
			free(data->pwd);
			data->pwd = 0;
			ft_free_env(data->env);
			data->env = 0;
			ft_free_env(cmdtab);
			ft_lstclear(&(data->token_list), ft_free_token);
			exit(127);
		}
	}
	free(data->pwd);
	data->pwd = 0;
	ft_free_env(data->env);
	data->env = 0;
	ft_free_env(cmdtab);
	ft_lstclear(&(data->token_list), ft_free_token);
	exit(code);
}

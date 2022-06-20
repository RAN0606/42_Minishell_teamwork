/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/20 14:36:04 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		ft_call_builtin(char **list_cmd, t_data *data)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
		exit(ft_echo(list_cmd));
	else if (!ft_strcmp(list_cmd[0], "pwd"))
		exit(ft_pwd());
	else if (!ft_strcmp(list_cmd[0], "cd"))
		exit(ft_cd(list_cmd, data));
	else if (!ft_strcmp(list_cmd[0], "env"))
		exit(ft_env(data));
	//else if (!ft_strcmp(list_cmd[0], "exit"))
	//	ft_exit(list_cmd);
	else if (!ft_strcmp(list_cmd[0], "export"))
		ft_export(list_cmd, data);
	else if (!ft_strcmp(list_cmd[0], "unset"))
		ft_unset(list_cmd, data);
	/*else
	{
		ft_exec(list_cmd, data);
	}*/
	return (-1);
}

int	ft_call_function(char **cmdtab, char **envtab, t_data *data)
{
	
	if (ft_call_builtin(cmdtab, data) == -1)
	{
		if(ft_excuvp(cmdtab, envtab)==-1)
		{
			printf("cmd not found\n");
			exit(127);
		}
	}
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/16 16:04:50 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int		ft_call_builtin(char **list_cmd)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
		exit(ft_echo(list_cmd));
	else if (!ft_strcmp(list_cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(list_cmd[0], "cd"))
		ft_cd(list_cmd, data);
	else if (!ft_strcmp(list_cmd[0], "env"))
		ft_env(data->env);
	else if (!ft_strcmp(list_cmd[0], "exit"))
		ft_exit(list_cmd, data);
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

int	ft_call_function(char **cmdtab, char **envtab)
{
	
	if (ft_call_builtin(cmdtab) == -1)
	{
		if(ft_excuvp(cmdtab, envtab)==-1)
		{
			printf("cmd not found\n");
			exit(127);
		}
	}
	return (0);
}


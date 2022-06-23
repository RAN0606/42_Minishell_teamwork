/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:43:52 by qxia              #+#    #+#             */
/*   Updated: 2022/06/23 12:47:30 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_pwd(t_data *data)
{
	char	*pwd;

	data->pwd = getcwd(NULL, 0);
	if (ft_index("PWD", data) >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		change_var(pwd, data, ft_index(pwd, data));
		free(pwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		data->env = export_env(data->env, pwd);
		free(pwd);
	}
}

void	change_env_oldpwd(t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	if (ft_index("OLDPWD", data) >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		oldpwd = ft_strjoin("OLD", pwd);
		change_var(oldpwd, data, ft_index("OLDPWD=", data));
		free(oldpwd);
		free(pwd);
	}
	else
		data->env = export_env(data->env, "OLDPWD");
	free(data->pwd);
}

int	change_pwd(t_data *data, char *input)
{
	char	*pwd;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, BUFFER_SIZE);
	if (!cwd && input && ft_strcmp(".", input) == 0)
	{
		ft_putstr_fd("Error retrieving current directory\n", 2);
		pwd = data->pwd;
		data->pwd = ft_strjoin(pwd, "/.");
		free(pwd);
	}
	if (cwd)
	{
		change_env_oldpwd(data);
		change_env_pwd(data);
	}
	free(cwd);
	return (1);
}

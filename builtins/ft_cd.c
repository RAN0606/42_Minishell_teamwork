/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:24:14 by qxia              #+#    #+#             */
/*   Updated: 2022/05/30 16:20:46 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//hander with only cd, but not cd -
// chdir() changes the current working directory of the calling process to the directory specified in path

int	cd_only(t_data	*data) //only has cd
{
	if (ft_index("HOME=", data) < 0 \
			|| chdir((strchr(data->env[ft_index("HOME=", data)], '=') + 1)) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int	cd_path(char **args, t_data *data)
{
	if (chdir(args[1]) == -1) //chdir returns -1 if it fails to change disectory
		return (0);
	change_pwd(data, args[1]);
	return (1);
}

void	ft_cd(char **args, t_data *data)
{
	if (!args[1])
	{
		if (!cd_only(data))
			return (error_message("cd: HOME: is undefined\n", 1));
	}
	if (args[1] && args[2])
		return (error_message("cd: too many arguments\n", 1));
	else
	{
		if (!cd_path(args, data))
			return (error_message("cd: no such file or dirsctory\n", 1));
	}
	g_status = 0;
}

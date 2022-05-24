/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:24:14 by qxia              #+#    #+#             */
/*   Updated: 2022/05/24 17:55:27 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_home_path(char	*path)
{
	char	*tmp;
	char	*tmp1;

	if (!ft_strcmp(path, "~"))
	{
		
	}
}
static int	change(char	*path, int home)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd);
			free(pwd);
		}
		if ((pwd = getcwd(NULL, 0)))
		{
			set_env("PWD", pwd);
			free(pwd);
		}
		if (home)
			free(path);
		return (1);
	}
	free(pwd);
	return (0);
}

static int	update_oldpwd(t_env *env)
{
	
}

int	ft_cd(char	**args)
{
	(void)av;

	ft(PWD);
	if (ft(cd == ""))	
}

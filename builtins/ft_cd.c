/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:24:14 by qxia              #+#    #+#             */
/*   Updated: 2022/05/27 16:53:56 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *args)
{
	ft_putstr_fd("cd :", 2);
	if (args(2))
		ft_putstr_fd("string not in pwd: ",2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

/*static char	*add_home_path(char	*path)
{
	char	*tmp;
	char	*tmp1;

	if (!ft_strcmp(path, "~"))
	{
		
	}
}*/

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int	i;
	int	j;
	int	size;

	while(env && env->next != NULL)
	{
		if (strcmp(env->value, var) == 0)
		{
			size = ft_strlen(env->value) - len;
			if (!(oldpwd = malloc(sizeof(char) * size + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	new_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(old = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	if (var_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memedel(oldpwd);
	return (0);

}

static int	find_path(int option, t_env *env)
{

}

int	ft_cd(char **args, t_env *env)
{
	int	ret;

	if (!args[1])
		return ()
	if (ft_strcmp(args[1], '-') == 0)
		ret = go_to_path(1, env);
	else
	{
		new_pwd(env);
		ret = chdir(args[1]);
		if (ret < 0)
			ret *= -1;
		if (ret != 0)
			print_error(args);
	}
	return (ret);
}

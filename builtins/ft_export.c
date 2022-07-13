/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:05:46 by qxia              #+#    #+#             */
/*   Updated: 2022/07/13 14:25:25 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_index(char *name, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] == name[j]
			&& name[j] != '\0' && name[j] != '='
			&& data->env[i][j] != '\0' && data->env[i][j] != '=')
			j++;
		if ((data->env[i][j] == '\0'
			|| data->env[i][j] == '=') && (name[j] == '\0'
			|| name[j] == '='))
			return (i);
		i++;
	}
	return (-1);
}

void	change_var(char *new_var, t_data *data, int index)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(new_var);
	}
}

void	export_only(t_data *data)
{
	int		i;
	int		j;
	char	**temp_env;
	char	*swap;

	i = 0;
	temp_env = data->env;
	while (temp_env[i + 1] && temp_env + i + 1)
	{
		j = i + 1;
		if (strcmp(temp_env[i], temp_env[j]) > 0)
		{
			swap = temp_env[j];
			temp_env[j] = temp_env[i];
			temp_env[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(temp_env);
}

int	ft_export(char **list_cmd, t_data *data)
{
	int	i;
	int	index;

	i = 0;
	if (list_cmd[1])
	{
		while (list_cmd[++i])
		{
			index = ft_index(list_cmd[i], data);
			if (index >= 0 && check_export(list_cmd[i]))
				change_var(list_cmd[i], data, index);
			else if (check_export(list_cmd[i]))
			{
				data->env = export_env(data->env, list_cmd[i]);
				if (!data->env)
					exit(EXIT_FAILURE);
			}
			else
				return (ft_perror("export: bad identifier\n", 1));
		}
	}
	else
		export_only(data);
	return (0);
}

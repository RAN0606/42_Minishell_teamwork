/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:05:46 by qxia              #+#    #+#             */
/*   Updated: 2022/06/22 10:16:32 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_index(char   *name, t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->env[i])
    {
        j = 0;
        while (data->env[i][j] && data->env[i][j] == name[j] && name[j] != '\0' && name[j] != '=' && data->env[i][j] != '\0' && data->env[i][j] != '=')
            j++;
        if ((data->env[i][j] == '\0' || data->env[i][j] == '=') && (name[j] == '\0' || name[j] == '='))
            return (i);
        i++;
    }
    return (-1);
}

void    change_var(char *new_var, t_data *data, int index)
{
    if (ft_strchr(new_var, '='))
    {
        free(data->env[index]);
        data->env[index] = ft_strdup(new_var);
    }
}

char    **export_env(char    **old_env, char *export)
{
    int     i;
    char    **new_env;

    i = 0;
    new_env = malloc(sizeof(char *) * (ft_envlen(old_env) + 2));
    if (!new_env)
        exit(EXIT_FAILURE);
    while (old_env[i])
    {
        new_env[i] = ft_strdup(old_env[i]);
        i++;
    }
    ft_free_env(old_env);
    new_env[i] = ft_strdup(export);
    i++;
    new_env[i] = NULL;
    return (new_env);
}

void    export_only(t_data *data)
{
    int i;
    int j;
    char    **temp_env;
    char    *swap;

    i = 0;
    temp_env = data->env;
    while (temp_env[i + 1] && temp_env+i+1)
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

int    ft_export(char **list_cmd, t_data *data)
{
    int i;
    int index;

    i = 1;
    if (list_cmd[i])
    {
        while (list_cmd[i])
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
			{
                ft_putstr_fd("export: bad identifier\n", 1);
				return (0);
			}
            i++;
        }
    }
    else
	{
		export_only(data);
	}
	return (0);
}

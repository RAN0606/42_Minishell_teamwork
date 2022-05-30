/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:05:46 by qxia              #+#    #+#             */
/*   Updated: 2022/05/30 15:29:05 by qxia             ###   ########.fr       */
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

void    change_var(char *new_var, t_data->data, int index)
{
    if (ft_strchr(new_var, '='))
    {
        free(data->env[index]);
        data->env[index] = ft_strdup(new_var);
    }
}

char    **export_env(har    **old_env, char *export)
{
    int     i;
    char    **new_env;

    i = 0;
    new_env = malloc(sizeof(char *) * (ft_envlen(old_env) + 1));
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:04:35 by qxia              #+#    #+#             */
/*   Updated: 2022/05/30 16:06:18 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **unset_env(char **old_env, int index)
{
    int i;
    int j;
    char    **new_env;

    i = 0;
    j = 0;
    new_env = malloc(sizeof(char *) * (ft_envlen(old_env)));
    if (!new_env)
        exit(EXIT_FAILURE);
    while (old_env[i])
    {
        if (i != index)
        {
            new_env[j] = ft_strdup(old_env[i]);
            j++;
        }
        i++;
    }
    ft_free_env(old_env);
    i--;
    new_env[i] = 0;
    return (new_env);
}

void    ft_unset(char   **inputs, t_data *data)
{
    int i;
    int index;

    i = 1;
    while (inputs[i])
    {
        if (check_export(inputs[i])) //check_export is in the ft_export_utils.c
        {
            index = ft_index(inputs[i], data);
            if (index > 0)
                data->env = unset_env(data->env, index);
            i++;
        }
        else
            return (error_message("unset: invalid identifier\n", 1));
    }
}
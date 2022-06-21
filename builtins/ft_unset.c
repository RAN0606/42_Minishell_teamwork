/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:04:35 by qxia              #+#    #+#             */
/*   Updated: 2022/06/21 16:35:37 by rliu             ###   ########.fr       */
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

int   ft_unset(char   **list_cmd, t_data *data)
{
    int i;
    int index;

    i = 1;
    while (list_cmd[i])
    {
        if (check_export(list_cmd[i])) //check_export is in the ft_export_utils.c
        {
            index = ft_index(list_cmd[i], data);
            if (index > 0)
                data->env = unset_env(data->env, index);
            i++;
        }
        //else
          //  ft_putstr_fd("unset: invalid identifier\n", 2);
    }
	return (0);
}

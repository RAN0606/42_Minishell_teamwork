/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:02:31 by qxia              #+#    #+#             */
/*   Updated: 2022/06/22 10:19:46 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_export(char *str)
{
    int i;

    i = 0;
    if (ft_isdigit(str[i]))
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void    print_export(char **env)
{
    int i;
    int j;
    int equal;

    i = 0;
    while (env[++i])
    {
        equal = 1;
        j = 0;
        ft_putstr_fd("declare -x ",1);
        while (env[i][j])
        {
            if (env[i][j] == '\\' || env[i][j] == '$' ||
            env[i][j] == '\"')
                write(1, "\\", 1);
            write(1, &env[i][j], 1);
            if (env[i][j] == '=' && equal-- == 1)
                write(1, "\"", 1);
            j++;
        }
        if (equal != 1)
            write(1, "\"", 1);
        write(1, "\n", 1);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:02:31 by qxia              #+#    #+#             */
/*   Updated: 2022/05/30 16:05:46 by qxia             ###   ########.fr       */
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
        if (!ft_isalnum(str[i] && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:05:16 by qxia              #+#    #+#             */
/*   Updated: 2022/06/09 14:58:25 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_strisdigit(char *str)
{
    size_t  i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

static int  check_nbr(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '-' || str[i] == '+')
            return (0);
        i++;
    }
    return (1);
}

void    ft_exit(char **inputs, t_data *data)
{
    if (inputs[1])
    {
        
    }
}
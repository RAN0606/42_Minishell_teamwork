/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:05:16 by qxia              #+#    #+#             */
/*   Updated: 2022/06/22 14:46:08 by rliu             ###   ########.fr       */
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

void    ft_exit(char   **cmd) //t_cmd pas encore defini
{
	int code;
	code = 0;
    if (!cmd)
        return ;
    else if (cmd && cmd[1] && cmd[2] && ft_strisdigit(cmd[1]))
    {
        ft_putstr_fd("mimishell: exit: too many arguments\n", 2);
        return;
    }
    else if (cmd && cmd[1]&& !(ft_strisdigit(cmd[1])) && !check_nbr(cmd[1]))
    {
        ft_putstr_fd("mimishell: exit: numeric argument required\n", 2);
        exit(2);
    }
    else
    {
        ft_putstr_fd("exit\n", 2);
		if (cmd[1])
			code = ft_atoi(cmd[1]);
        exit(code);
    }
}

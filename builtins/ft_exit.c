/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:05:16 by qxia              #+#    #+#             */
/*   Updated: 2022/07/13 11:47:07 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisdigit(char *str)
{
	size_t	i;

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

static int	check_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd, t_data *data)
{
	int	code;

	code = 0;
	if (!cmd)
		return (0);
	else if (cmd && cmd[1] && cmd[2] && ft_strisdigit(cmd[1]))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("mimishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (cmd && cmd[1] && (!(ft_strisdigit(cmd[1])) || !check_nbr(cmd[1])))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("mimishell: exit: numeric argument required\n", 2);
		ft_free_env(cmd);
		ft_lstclear(&(data->token_list), ft_free_token);
		ft_free_env(data->env);
		free(data->pwd);
		exit(2);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		if (cmd[1])
			code = ft_atoi(cmd[1]);
		g_status = code;
		ft_free_env(cmd);
		ft_lstclear(&(data->token_list), ft_free_token);
		ft_free_env(data->env);
		free(data->pwd);
		exit(code);
	}
	return (0);
}

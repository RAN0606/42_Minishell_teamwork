/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qinxia <qinxia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:07:54 by qxia              #+#    #+#             */
/*   Updated: 2022/05/18 23:22:56 by qinxia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_number(char **args)
{
	int	num;

	num = 0;
	while(args[num])
	{
		num++;
	}
	return (num);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args_number(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0) //if -n exist; while pour -nnnnnnnn
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1); //put " " between two token
			i++;
		}
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (0);
}

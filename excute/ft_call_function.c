/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/15 18:50:46 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		ft_call_builtin(char **list_cmd)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
		exit(ft_echo(list_cmd));
	return (-1);
}

int	ft_call_function(char **cmdtab, char **envtab)
{
	
	if (ft_call_builtin(cmdtab) == -1)
	{
		if(ft_excuvp(cmdtab, envtab)==-1)
		{
			printf("cmd not found\n");
			exit(127);
		}
	}
	return (0);
}


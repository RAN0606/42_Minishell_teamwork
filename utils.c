/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:28:32 by rliu              #+#    #+#             */
/*   Updated: 2022/05/18 12:28:23 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_checkenv(char *key, char **envtab) // check if the keyword is exit
{
	int i;

	i = 0;
	while (*(envtab + i))
	{
		if (!ft_strncmp(envtab[i], key, ft_strlen(key)))
				return (i);
		i++;
	}
	return (-1);
}

void ft_print_value(char *key, char **envtab)
{
	int index;
	
	index = -2;
	index = ft_checkenv(key, envtab);
	if (index == -1)
		printf("\n");
	else if (index > 0)
		printf("%s\n", envtab[index] + ft_strlen(key));
}



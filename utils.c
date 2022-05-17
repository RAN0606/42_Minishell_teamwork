/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:57:45 by rliu              #+#    #+#             */
/*   Updated: 2022/05/17 17:07:19 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_checkenv(char *key, char **envtab)
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





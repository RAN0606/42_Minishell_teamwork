/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/26 21:01:47 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_envvalue(char *keyequal, char **envtab)
{
	int	i;

	i = 0;
	while (*(envtab + i))
	{
		if (!ft_strncmp(envtab[i], keyequal, ft_strlen(keyequal)))
			return (i);
		i++;
	}
	return (-1);
}


char	*ft_return_envvalue(char *key, char **envtab)
{
	char	*keyequal;
	int		index;

	keyequal = ft_strjoin(key, "=");
	index = -2;
	index = ft_check_envvalue(key, envtab);
	if (index >= 0)
		return (ft_strdup(envtab[index] + ft_strlen(keyequal)));
	return (ft_strdup(""));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:00:09 by qxia              #+#    #+#             */
/*   Updated: 2022/05/30 15:27:42 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_free_env(char **envtab)
{
	int i;
	
	i = 0;
	while(*(envtab + i))
		free(envtab[i++]);
	free(envtab);
}

int	ft_envlen(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

char	**ft_getenv(char **env)
{
	int		i;
	char	**envtab;
	
	i = 0;
	while (*(env+i))
		i++;		
	envtab = (char **)malloc(sizeof(char *) * (i+1));
	i = 0;
	while (*(env + i))
	{
		envtab[i] = ft_strdup(*(env+i));
		i++;
	}
	envtab[i] = 0;
	return (envtab);
}

void ft_env(char **envtab)// this is just a test for env
{
	int i;

	i = 0;
	while (*(envtab+i))
		printf("%s\n", envtab[i++]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:57:50 by rliu              #+#    #+#             */
/*   Updated: 2022/06/21 10:36:42 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_free_excvp(char **pathlist, char *cmdpath, char *path)
{
	char **temp;
	temp = pathlist-1;
	while (*(++temp))
		free(*temp);
	free(*temp);
	free(pathlist);
	free(cmdpath);
	free(path);
}		
int	ft_excuvp(char **simplecmd, char **envtab)
{
	char *path;
	char **pathlist;
	char **temp;
	char *cmdpath;

	path = ft_return_envvalue("PATH", envtab);
	pathlist = ft_split(path, ':');
	temp = pathlist - 1;
	cmdpath = ft_strjoinfree(ft_strdup("/"), ft_strdup(*simplecmd));
	execve(simplecmd[0], simplecmd, envtab);
	while (*(++temp))
		*temp = ft_strjoinfree(*temp, ft_strdup(cmdpath));
	temp = pathlist - 1;
	while (*(++temp))
		execve(*temp, simplecmd, envtab);
	ft_free_excvp(pathlist, cmdpath, path);
	return (-1);
}

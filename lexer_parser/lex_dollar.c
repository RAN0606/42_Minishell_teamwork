/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/06/27 12:44:17 by rliu             ###   ########.fr       */
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

int	ft_check_envkey(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
		if (cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == '\'')
			return (i);
	return (i);
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

char	*ft_dollar_inword(char *temp_cmd, char **envtab, t_word *word)
{
	char	*env_key;
	char	*env_value;
	int		j;

	j = 0;
	if (*(temp_cmd + 1) == '\'')
		return (temp_cmd + 1);
	j = ft_check_envkey(temp_cmd);
	if (j == 1)
		word->str = ft_strjoinfree(word->str, ft_strdup("$"));
	else
	{
		env_key = ft_substr(temp_cmd, 1, j - 1);
		if (ft_strcmp("?", env_key) == 0)
			env_value = ft_itoa(g_status);
		else
			env_value = ft_return_envvalue(env_key, envtab);
		free(env_key);
		word->str = ft_strjoinfree(word->str, env_value);
	}	
	return (temp_cmd + j);
}

char	*ft_handle_dollar(char *cmd, char **envtab)
{
	char	*env_key;
	char	*env_value;
	int		j;

	j = ft_check_envkey(cmd);
	if (j == 1)	
		return (ft_strdup("$"));
	else if (j > 1)
	{
		env_key = ft_substr(cmd, 1, j - 1);
		if (ft_strcmp("?", env_key) == 0)
			env_value = ft_itoa(g_status);
		else
			env_value = ft_return_envvalue(env_key, envtab);
		free(env_key);
		return (env_value);
	}	
	return (0);
}

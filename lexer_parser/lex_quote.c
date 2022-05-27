/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/27 20:59:00 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_chr_quote(char *cmd, char c)
{
	int	i;
	
	i = 0;
	while (cmd[++i])
	{
		if (cmd[i] == c)
			return (i);
	}
	return (-1);		
}

char	*ft_return_quotevalue(char *cmd, char c, char **envtab, int j)
{
	int	i;
	char	*str;

	str = ft_strdup("");
	i = -1;
	while (++i < j -1)
	{
		if (cmd[i] == '$' && c =='\"')
		{	
			str = ft_strjoinfree(str, ft_handle_dollar(cmd, envtab));
			i = ft_check_envkey(cmd) - 1;
		}
		else 
			str = ft_strjoinfree(str, ft_substr(cmd, i, 1));
	}
	return (str);
}

char *ft_handle_quote (char *temp_cmd, t_word *word, char **envtab)
{
	int j;

	j = ft_chr_quote(temp_cmd, *temp_cmd);
	if (j < 0)
	{
		printf("parsing error: quote is not closed (don't need to do it - 42 subject)");
		return (NULL);
	}
	else
		word->str = ft_strjoinfree(word->str, ft_return_quotevalue(temp_cmd + 1, *temp_cmd, envtab, j));
	return (temp_cmd + j + 1);
}

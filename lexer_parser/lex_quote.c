/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/30 16:28:55 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chr_quote(char *cmd_wqt, char c)
{
	int	i;

	i = 0;
	while (cmd_wqt[++i])
	{
		if (cmd_wqt[i] == c)
			return (i);
	}
	return (i);
}

char	*ft_return_quotevalue(char *cmd_wqt, char c, char **envtab, int j)
{
	int		i;
	char	*str;

	str = ft_strdup("");
	i = 0;
	while (++i < j)
	{
		if (cmd_wqt[i] == '$' && c == '\"')
		{
			str = ft_strjoinfree(str, ft_handle_dollar(cmd_wqt + i, envtab));
			i = ft_check_envkey(cmd_wqt + i);
		}
		else
			str = ft_strjoinfree(str, ft_substr(cmd_wqt, i, 1));
	}
	return (str);
}

char	*ft_handle_quote(char *cmd_wqt, t_word *word, char **envtab)
{
	int	j;

	j = ft_chr_quote(cmd_wqt, *cmd_wqt);
	if (!cmd_wqt[j])
	{	
		printf("parsing error: quote is not closed (42 subject)\n");
		free(word->str);
		free(word);
		return (NULL);
	}
	else
	{
		word->str = ft_strjoinfree(word->str,
				ft_return_quotevalue(cmd_wqt, *cmd_wqt, envtab, j));
	}
	return (cmd_wqt + j + 1);
}

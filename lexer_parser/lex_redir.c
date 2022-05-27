/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/27 20:22:23 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (0);
	s = (char *)malloc(sizeof(*s) * ((ft_strlen(s1) + (ft_strlen(s2) + 1))));
	if (!s)
		return (0);
	ft_strlcpy(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (s);
}


char	*ft_handle_redir(char *cmd, t_list **token_list)
{
	if (*cmd == '>')
	{
		if (*++cmd == '>')
			ft_add_token_element(token_list,L_APPEND,">>");
		else
			ft_add_token_element(token_list,L_OUTPUT,">");
	}
	else if (*cmd == '<')
	{
		if (*++cmd == '<')
			ft_add_token_element(token_list,L_HEREDOC,"<<");
		else
		
			ft_add_token_element(token_list,L_INPUT, "<");
	}
	return (cmd);
}

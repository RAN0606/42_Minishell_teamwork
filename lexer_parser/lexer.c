/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/06/27 12:07:36 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lexer(char *cmd, char **envtab)
{
	char	*temp_cmd;
	t_list	*token_list;

	token_list = NULL;
	temp_cmd = cmd - 1;
	while (*(++temp_cmd))
	{
		if (*temp_cmd == ' ')
			continue ;
		else if (*temp_cmd == '|')
			ft_add_token_element(&token_list, L_PIPE, "|");
		else if (*temp_cmd == '>' || *temp_cmd == '<')
			temp_cmd = ft_handle_redir(temp_cmd, &token_list);
		else
			temp_cmd = ft_add_word(temp_cmd, &token_list, envtab);
		if (!temp_cmd)
			return (NULL);
	}
	return (token_list);
}

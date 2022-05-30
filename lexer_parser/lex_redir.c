/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/30 16:30:13 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_redir(char *cmd, t_list **token_list)
{
	if (*cmd == '>')
	{
		if (*++cmd == '>')
			ft_add_token_element(token_list, L_APPEND, ">>");
		else
			ft_add_token_element(token_list, L_OUTPUT, ">");
	}
	else if (*cmd == '<')
	{
		if (*++cmd == '<')
			ft_add_token_element(token_list, L_HEREDOC, "<<");
		else
			ft_add_token_element(token_list, L_INPUT, "<");
	}
	return (cmd);
}

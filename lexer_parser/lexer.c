/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/27 20:23:56 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_token(int token, char *str)
{
	t_token	*token_ptr;
	t_list	*token_element;

	token_ptr = malloc(sizeof(t_token));
	if (!token_ptr)
		return 0;
	token_ptr->token = token;
	token_ptr->str = ft_strdup(str);
	token_element = ft_lstnew((void *)token_ptr);
	return (token_element);

}

int	ft_add_token_element(t_list **token_list, int token, char *str)
{
	t_list	*token_element;

	token_element = ft_token(token, str);
	if (!token_element)
	{
		ft_lstclear(token_list,ft_free_token);
		return (0);
	}
	ft_lstadd_back(token_list, token_element);
	return (1);
}


t_list	*ft_lexer(char *cmd, char **envtab)
{

	char	*temp_cmd;
	t_list	*token_list;

	token_list = NULL;
	temp_cmd = cmd - 1;
	while (*++temp_cmd)
	{
	       if (*temp_cmd == ' ')	
		       continue ;
	       else if (*temp_cmd == '|')	       
		       ft_add_token_element(&token_list, L_PIPE, "|");	
	       else if (*temp_cmd == '>' || *temp_cmd == '<')
		       temp_cmd = ft_handle_redir(temp_cmd, &token_list);
	       else
		       temp_cmd = ft_add_word(temp_cmd, &token_list, envtab);
	}
	return (token_list);
}

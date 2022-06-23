/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/23 15:49:57 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_syntax(t_list *lex_list)
{
	t_list	*list_ptr;
	int		last_token;

	last_token = 0;
	list_ptr = lex_list;
	while (list_ptr)
	{
		if (last_token == 0
			&& ((t_token *)(list_ptr->content))->token == L_PIPE)
		{
			printf("minish: syntax error near unexpected token `|'\n");
			return (1);
		}
		else if (last_token > L_WORD
			&& (((t_token *)(list_ptr->content))->token > L_WORD))
		{
			printf("minish: syntax error near unexpected token `%s'\n",
				((t_token *)(list_ptr->content))->str);
			return (1);
		}
		last_token = ((t_token *)(list_ptr->content))->token;
		list_ptr = list_ptr->next;
	}
	if (last_token > L_WORD)
	{
		printf("minish: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

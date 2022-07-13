/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/13 17:25:05 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_save_heredoc(t_list *list_ptr)
{
	char	*name;
	int		code;

	code = 0;
	name = ft_tmpname();
	code = ft_heredoc(list_ptr, name);
	if (code != 0)
	{
		unlink(name);
		free(name);
		return (130);
	}
	else
	{
		free(((t_token *)(list_ptr->content))->str);
		((t_token *)(list_ptr->content))->str = name;
		((t_token *)(list_ptr->content))->is_save = 1;
	}
	return (0);
}

int	ft_check_heredoc(t_list *lex_list)
{
	t_list	*list_ptr;
	int		token;
	int		code;

	list_ptr = lex_list;
	code = 0;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_HEREDOC)
		{
			list_ptr = list_ptr->next;
			code = ft_save_heredoc(list_ptr);
			if (code == 130)
				return (130);
		}
		list_ptr = list_ptr->next;
	}
	return (code);
}

int	ft_p_syntaxerr(int nb, char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (nb);
}

int	ft_check_syntax(t_list *lex_list)
{
	t_list	*list_ptr;
	int		last_token;

	last_token = 0;
	list_ptr = lex_list;
	while (list_ptr)
	{
		if (last_token == 0 && ((t_token *)(list_ptr->content))->token
			== L_PIPE)
			return (ft_p_syntaxerr(1, "syntax er`|'\n"));
		else if (last_token > L_WORD
			&& (((t_token *)(list_ptr->content))->token > L_WORD))
			return (ft_p_syntaxerr(1, ((t_token *)(list_ptr->content))->str));
		last_token = ((t_token *)(list_ptr->content))->token;
		list_ptr = list_ptr->next;
	}
	if (last_token > L_WORD)
		return (ft_p_syntaxerr(1, "newline"));
	if (ft_check_heredoc(lex_list) != 0)
		return (130);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:00:52 by rliu              #+#    #+#             */
/*   Updated: 2022/07/13 11:57:02 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*s;

	if (!s2)
		return (s1);
	if (!s1)
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

void	ft_free_token(void *token)
{
	if (((t_token *)token)->is_save == 1)
		unlink(((t_token *)token)->str);
	//ft_print_token (token);
	free(((t_token *)token)->str);
	free((t_token *)token);
}

void	ft_print_token(void *token)
{
	printf("token: %d, str :%s\n",
		((t_token *)token)->token, ((t_token *)token)->str);
}

t_list	*ft_token(int token, char *str)
{
	t_token	*token_ptr;
	t_list	*token_element;

	token_ptr = malloc(sizeof(t_token));
	if (!token_ptr)
		return (0);
	token_ptr->token = token;
	token_ptr->str = ft_strdup(str);
	token_ptr->is_save = 2;
	token_element = ft_lstnew((void *)token_ptr);
	return (token_element);
}

int	ft_add_token_element(t_list **token_list, int token, char *str)
{
	t_list	*token_element;

	token_element = ft_token(token, str);
	if (!token_element)
	{
		ft_lstclear(token_list, ft_free_token);
		return (0);
	}
	ft_lstadd_back(token_list, token_element);
	return (1);
}

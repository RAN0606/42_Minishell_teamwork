/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/13 11:59:38 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_input(t_list *lex_list)
{
	char	*path;

	if (lex_list)
	{
		path = ((t_token *)(lex_list->content))->str;
		if (access(path, F_OK) != 0)
		{
			printf("%s: No such file or directory\n", path);
			return (1);
		}
	}
	return (0);
}

int	ft_check_input(t_list *lex_list)
{
	t_list	*list_ptr;
	int		token;

	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			break ;
		else if (token == L_INPUT)
		{
			list_ptr = list_ptr->next;
			if (ft_input(list_ptr) == 2)
				return (2);
		}
		list_ptr = list_ptr->next;
	}
	return (0);
}

int	ft_redir_in_dup(char *lastin_name)
{
	int	fd;

	if (lastin_name != 0)
	{
		fd = open(lastin_name, O_RDONLY);
		if (fd < 0)
		{
			perror("fd:");
			return (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

int	ft_redir_in(t_list *lex_list)
{
	int		token;
	t_list	*list_ptr;
	char	*lastin_name;

	lastin_name = 0;
	list_ptr = lex_list;
	if (ft_check_input (list_ptr) == 2)
		return (1);
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			break ;
		else if (token == L_INPUT || token == L_HEREDOC)
		{
			list_ptr = list_ptr->next;
			lastin_name = ((t_token *)(list_ptr->content))->str;
		}
		list_ptr = list_ptr->next;
	}
	return (ft_redir_in_dup(lastin_name));
}

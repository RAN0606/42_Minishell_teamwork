/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/17 17:09:27 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		ft_output(t_list *lex_list)
{
	char *name;
	int	 fd;

	name = ((t_token *)(lex_list->content))->str;
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd <0)
		return (-1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		ft_append(t_list *lex_list)
{
	char *name;
	int	 fd;

	name = ((t_token *)(lex_list->content))->str;
	fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		return (-1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		ft_redir_out(t_list *lex_list)
{
	int		token;
	t_list  *list_ptr;
	int		stdfd;
	
	stdfd=dup(1);
	list_ptr = lex_list;
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		if (token == L_PIPE)
			return (0);
		else if (token == L_OUTPUT)
		{
			list_ptr = list_ptr->next;
			if (ft_output(list_ptr) < 0)
				return (-1);
		}
		else if (token == L_APPEND)
		{	
			list_ptr = list_ptr->next;
			if (ft_append(list_ptr) < 0)
				return (-1);
		}	
		list_ptr = list_ptr->next;
	}
	dup2(stdfd,1);
	return (0);
}


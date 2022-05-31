/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/05/31 17:21:55 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmdtab *ft_count_pipe (t_list *lex_list)
{
	int	size;
	t_list	*list_ptr;
	t_cmdtab *cmdtab;
	t_list	*cmdtab_list;

	size = 0;
	list_ptr =lex_list;
	cmdtab = (t_cmdtab *)ft_calloc(1, sizeof(t_cmdtab));
	while (list_ptr)
	{
		if (((t_token *)(list_ptr->content))->token == L_INPUT)
		{

		}

			
		list_ptr = list_ptr->next;
	}
	return (cmd_tabs);
}

t_cmdtab *ft_return_cmdtab(t_list *lex_list, t_cmdtab *cmd_tab)
{
	int	i;
	
	i = 0;	
	while (list_ptr)
	{
		if ((t_token *)->)
	}



}

char	**parser_cmd(t_list *lex_list)
{
	int	size;
	t_list	*list_ptr;
	char	**list_cmd;
	int	i;
//	printf("text1");
	size = 0;
	list_ptr = lex_list;
	while (list_ptr)
	{
		if (((t_token *)(list_ptr->content))->token == L_WORD)
			size++;
		list_ptr = list_ptr->next;
	}	
	list_cmd = (char **)ft_calloc(size+1, sizeof(char *));
	if (!list_cmd)
		return NULL;
	i = -1;
	list_ptr = lex_list;
	while (list_ptr)
	{
		if (((t_token *)(list_ptr->content))->token == L_WORD)
			list_cmd[++i] = ((t_token *)(list_ptr->content))->str;
		list_ptr = list_ptr->next;
	}
	i = -1;
	return (list_cmd);
}

void	ft_call_builtin(char **list_cmd)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
			ft_echo(list_cmd);
	free(list_cmd);
}

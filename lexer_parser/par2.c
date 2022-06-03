/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/03 19:31:56 by rliu             ###   ########.fr       */
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
        if (last_token == 0 && ((t_token *)(list_ptr->content))->token == L_PIPE)
        {
			printf("minish: syntax error near unexpected token `|'");
			return (1);
		}
		if (last_token > L_WORD && 
			(((t_token *)(list_ptr->content))->token != L_WORD))
		{
			printf("minish: syntax error near unexpected token `|'");
			return (1);
		}
		last_token = ((t_token *)(list_ptr->content))->token;
		list_ptr = list_ptr->next;
	}
	if (last_token > L_WORD)
	{
			printf("minish: syntax error near unexpected token `newline'");
			return (1);
	}
	return (0);
}

int ft_count_simple_cmd(t_list *lex_list)
{
	t_list	*lptr;
	int 	token;
	int		size;
	printf("testcount");
	lptr = lex_list;
	size = 0;
	token = 0;
	while (lptr)
	{
		token = ((t_token *)(lptr->content))->token;
		if (token == L_PIPE)
			break ;
		else if (token > L_INPUT)
			lptr= lptr->next;
		else if (token == L_WORD)
			size++;
	}
	return (size);
}

void ft_save_simple_cmd(t_list *lex_list, char **cmdtab)
{
	t_list	*lptr;
	int 	token;
	int		i;

	i = -1;
	lptr = lex_list;
	while (lptr)
	{
		printf("testwhile");
		token = ((t_token *)(lptr->content))->token;
		if (token == L_PIPE)
			return ;
		else if (token > L_INPUT)
			lptr= lptr->next;
		else if (token == L_WORD)
			cmdtab[++i] = ((t_token *)(lptr->content))->str;
		lptr = lptr->next; 			
	}
	printf("testsave %s", cmdtab[0]);
}

char **ft_creat_simple_cmd(t_list *lptr)
{
	char	**cmdtab;
	int 	size;

	size = ft_count_simple_cmd(lptr);
	cmdtab = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!cmdtab)
		return (NULL);
	ft_save_simple_cmd(lptr, cmdtab);
	return (cmdtab);
	printf("test2");
}

t_list *ft_find_pipe(t_list *lex_list)
{
	t_list	*lptr;
	int		token;

	lptr = lex_list;	
	while (lptr)
	{
		token = ((t_token *)(lptr->content))->token;
		if (token == L_PIPE)
			return (lptr->next);
		lptr = lptr->next;
	}
	return (lptr);
}

int	ft_call_builtin(char **list_cmd)
{
	if (ft_strcmp(list_cmd[0],"echo") == 0)
			ft_echo(list_cmd);
//	else if (ft_strcmp(list_cmd[0]," ") == 0)

	else 
		return (1);
	return (0);
}

void ft_excuve_cmd(t_list *lex_list)
{
	char **cmdtab;

	
	printf("testexcuve");
	cmdtab = ft_creat_simple_cmd(lex_list);
	printf("test: %s", cmdtab[0]);
	if (!cmdtab)
		return ;
	ft_call_builtin(cmdtab);
	free(cmdtab);
}

void parser_cmd(t_list *lex_list)
{
		printf("testparser");
		//ft_redir_int(lex_list);
		ft_excuve_cmd(lex_list);
		//ft_redir_out(lex_list);
}


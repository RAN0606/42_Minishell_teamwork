/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_excute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/07/19 16:29:27 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_count_simple_cmd(t_list *lex_list)
{
	int		size;
	t_list	*list_ptr;

	size = 0;
	list_ptr = lex_list;
	while (list_ptr && ((t_token *)(list_ptr->content))->token != L_PIPE)
	{
		if (((t_token *)(list_ptr->content))->token != L_WORD)
			list_ptr = list_ptr->next;
		else if (((t_token *)(list_ptr->content))->token == L_WORD)
			size++;
		list_ptr = list_ptr->next;
	}
	return (size);
}

char	**ft_save_simple_cmd(t_list *lex_list)
{
	int		size;
	int		i;
	char	**list_cmd;
	t_list	*list_ptr;

	size = ft_count_simple_cmd(lex_list);
	if (size == 0)
		return (0);
	list_cmd = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!list_cmd)
		return (0);
	i = -1;
	list_ptr = lex_list;
	while (list_ptr && ((t_token *)(list_ptr->content))->token != L_PIPE)
	{
		if (((t_token *)(list_ptr->content))->token != L_WORD)
			list_ptr = list_ptr->next;
		else if (((t_token *)(list_ptr->content))->token == L_WORD)
			list_cmd[++i] = ft_strdup(((t_token *)(list_ptr->content))->str);
		list_ptr = list_ptr->next;
	}
	return (list_cmd);
}

int	ft_simplecmd(t_data *data)
{
	char	**simple_cmd;
	int		oldfd[2];
	int		code;

	code = 0;
	oldfd[0] = dup(0);
	oldfd[1] = dup(1);
	code = ft_redir_in(data->token_list);
	if (code)
		return (code);
	ft_redir_out(data->token_list);
	simple_cmd = ft_save_simple_cmd(data->token_list);
	if (!simple_cmd)
		return (0);
	code = ft_call_function(simple_cmd, data);
	ft_free_env(simple_cmd);
	dup2(oldfd[0], 0);
	dup2(oldfd[1], 1);
	close(oldfd[0]);
	close(oldfd[1]);
	return (code);
}

int	ft_parser_cmd(t_data *data)
{
	t_list	*list_ptr;
	t_list	*next_cmd;
	int		code;

	list_ptr = data->token_list;
	if (ft_check_syntax(data))
		return (-1);
	next_cmd = ft_next_pipecmd(list_ptr);
	if (next_cmd)
		code = ft_pipe(list_ptr, data);
	else if (list_ptr)
		code = ft_simplecmd(data);
	g_ms.status = code;
	return (code);
}

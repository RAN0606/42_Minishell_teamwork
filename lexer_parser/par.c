/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:30:53 by rliu              #+#    #+#             */
/*   Updated: 2022/06/03 12:33:37 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_syntax(t_list *lex_list)
{
	t_list	*list_ptr;
	int	last_token_value;
	int	token
	
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

int	ft_count_pipe(t_list *lex_list)
{
	int	size;
	t_list	*list_ptr;

	size = 0;
	list_ptr =lex_list;
	while (list_ptr)
	{
		if (((t_token *)(list_ptr->content))->token == L_PIPE)
			size++;
		list_ptr = list_ptr->next;
	}
	return (size);
}

t_list	*ft_count_token(t_list *lex_list, int *count)
{
	int		token;
	t_list	*list_ptr;
	t_token	*token_ptr;

	token = 0;
	list_ptr = lex_list;
	ft_bzero((void *)count, sizeof(int)* 7);
	while (list_ptr)
	{
		token = ((t_token *)(list_ptr->content))->token;
		count[token]++;
		if (token == L_PIPE)
		{
			list_ptr = list_ptr->next;
			break;
		}
		list_ptr = list_ptr->next;
	}
	count[L_WORD] = count[L_WORD] - count[L_INPUT] - count[L_OUTPUT] - count[L_APPEND] - count[L_HEREDOC]; 	
	return (list_ptr);
}

void 	ft_free_cmdtab(t_cmd	*cmdtab)
{
	if (cmdtab->word_tab)
		free(cmdtab->word_tab);
	if (cmdtab->redir_in)
		free(cmdtab->redir_in);
	if (cmdtab->redir_out)
		free(cmdtab->redir_out);
	if (cmdtab->redir_hd)
		free(cmdtab->redir_hd);
	if (cmdtab->redir_apd)
		free(cmdtab->redir_apd);
	if (cmdtab)
		free(cmdtab);
}

/*int		ft_init_cmdtab(t_cmdtab *cmdtab, int *count)
{
	cmdtab = (t_cmdtab *)ft_calloc(sizof(t_cmdtab));
	cmdtab->word_tab = (char **)ft_calloc(count[L_WORD] + 1, sizeof(char *));
	cmdtab->redir_in = (char **)ft_calloc(count[L_INPUT] + 1, sizeof(char *));
	cmdtab->redir_out = (char **)ft_calloc(count[L_OUTPUT] + 1 , sizeof(char *));
	cmdtab->redir_hd = (char **)ft_calloc(count[L_HEREDOC] + 1, sizeof(char *));
	cmdtab->redir_apd = (char **)ft_calloc(count[L_APPEND] + 1, sizeof(char *));
	if (!cmdtab->word_tab || !cmdtab->redir_in || !cmdtab->redir_out|| 
		!cmdtab->redir_hd || !cmdtab->redir_apd)
	{
		ft_free_cmdtab(cmdtab);
		return (1);
	}
	return (0);
}*/

int	ft_free_cmdtab(char ***ptr)
{
	int i;
	i = 0;
	while (++i <= L_HEREDOC)
	{
		if (ptr[i])
			free (ptr[i]);
	}
	free (ptr);
}

char ***ft_init_cmdtab(int *count)
{
	int i;
	char	***cmdtab;

	i = 0;
	cmdtab =  (char ***)ft_calloc(7, sizeof(char **));
	if (!cmdtab)
		return (NULL);
	while (++i <= L_HEREDOC)
	{
		cmdtab[i] = (char **)ft_calloc(count[i]+1, sizeof(char *));
		if (!cmdtab[i])
		{
			ft_free_cmdtab(cmdtab);
			return (NULL);
		}
	}
	return (cmdtab);
}

void ft_save_str(t_list *lex_list, char ***cmdtab, int token_save)
{
	t_list			*list_ptr;
	char			***cmdtab;
	t_token 		*token_ptr;
	int				i;

	i= -1;
	list_ptr = lex_list;
	while (list_ptr)
	{
		token_ptr = ((t_token *)(list_ptr->content))->token;
		if (tr->token = token_save)
			token_ptr->str 
	}

	}
char ***ft_save_cmdtab(t_list *lex_list)
{
	t_list			*list_ptr;
	char			***cmdtab;
	int				count[7];
	
	ft_count_token(list_ptr, count);
	cmdtab = ft_init_cmdtab(cmdtab, count);
	if (!cmdtab)
		return (0);
	{
		
	
	}

}

int	ft_creat_cmdtabs(t_list *lex_list)
{
	char		***cmdtab_tab;
	int			nb_pipe;
	int			i;
	t_list		*list_ptr;
	
	if (ft_check_syntax(lex_list))
		return (1);
	nb_pipe = ft_count_pipe(lex_list);
	cmdtab_tab = (char ****)ft_calloc(ft_count_pipe(nb_pipe + 2, sizeof(char ***));
	i = -1;
	while (++i <= nb_pipe)
	{
		cmdtab_tab[i] = ft_cerat_cmdtab(ft)

	}

	
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

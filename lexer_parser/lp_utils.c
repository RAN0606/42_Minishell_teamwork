/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/26 21:11:49 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*s;

	if (!s1 || !s2)
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

int ft_check_envkey(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '"' || cmd[i] =='\'' )
			return (i-1);
		i++;
	}
	return (i-1);
}
char	*ft_handle_dollar(char *cmd, int i, char **envtab)
{
	char	*env_key;
	char	*env_value;
	int	j;

	j = ft_check_envkey(cmd, i + 1);
	if (i == j)
	{
		return (ft_strdup("$"));
	}
	else if (j > i)
	{
		env_key = ft_substr(cmd, i + 1, j - i);
		env_value = ft_return_envvalue(env_key, envtab);
		return (env_value);
	}	
	return (0);	
}

int	ft_chr_c(char *cmd, char c)
{
	int	i;
	i = -1;

	while (cmd[++i])
	{
		if (cmd[i] == c)
			return (i);
	}
	return (-1);		
}

char	*ft_return_quotevalue(char *cmd, char c, char **envtab)
{
	int 	j;
	int	i;
	char	*str;

	str = ft_strdup("");
	j = ft_chr_c(cmd, c);
	if (j < 0)
	{
		printf("parsing error: quote is not closed (don't need to do it - 42 subject)");
		return (0);
	}
	i = -1;
	while (++i < j)
	{
		if (cmd[i] == '$' && c =='\"')
		{	
			str = ft_strjoinfree(str, ft_handle_dollar(cmd, i, envtab));
		
			i = ft_check_envkey(cmd, i + 1);
		}
		else 
			str = ft_strjoinfree(str, ft_substr(cmd, i, 1));
			
	}
	return (str);
}

t_word	*ft_readword(char *temp_cmd, char **envtab)
{
	int	i;
	int	j;
	char	*env_value;
	t_word	*word;

	i=0;
	j=-1;	
	word = malloc(sizeof(t_word));
	word->str = ft_strdup("");
	while (temp_cmd[i])
	{
		if (temp_cmd[i] == '\'' || temp_cmd[i] == '"')
		{
			j = ft_chr_c(temp_cmd + i + 1, temp_cmd[i]);
			word->str = ft_strjoinfree(word->str, ft_return_quotevalue(temp_cmd + i + 1, temp_cmd[i], envtab));
			i = i + 2 + j;
		}
		else if (temp_cmd[i] == '$')
		{
			if(temp_cmd[i + 1] =='\'')
				i++;
			else
			{
				env_value = ft_handle_dollar(temp_cmd, i, envtab);
				if (env_value)
				{
					word->str = ft_strjoinfree(word->str, env_value);
					i =  ft_check_envkey(temp_cmd, i + 1) + 1;
				}
			}
		}
		else if (temp_cmd[i] ==' ' || temp_cmd[i] =='<' || temp_cmd[i] == '>' )
		{
			word->nb = i;
			return (word);
		}
		else
		{
			word->str = ft_strjoinfree(word->str, ft_substr(temp_cmd, i, 1));
			i++;
		}
	}
	word->nb = i;
	return (word);
}

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
int	ft_add_token_element(t_list *token_list, int token, char *str)
{
	t_list	*token_element;

	token_element = ft_token(token, str);
	if (!token_element)
	{
		ft_lstclear(&token_list,ft_free_token);
		exit (1);
	}
	ft_lstadd_back(&token_list, token_element);
	return (0);
}

char	*ft_handle_redir(char *cmd, t_list *token_list)
{
	if (*(cmd) == '>')
	{
		if (*(++cmd) == '>')
			ft_add_token_element(token_list,L_APPEND,">>");
		else
			ft_add_token_element(token_list,L_OUT,">");
	}
	else if (*cmd == '<')
	{
		if (*(++cmd) == '<')

			ft_add_token_element(token_list,L_HEREDOC,"<<");
		else
		
			ft_add_token_element(token_list,L_IN, "<");
	}
	return (++cmd);
}

char	*ft_add_word(char *cmd, t_list *token_list, char **envtab)
{
	t_word	*word;
	
	word = ft_readword(cmd, envtab);
	if (!word)
	{
		ft_lstclear(&token_list, ft_free_token);
		return 0;
	}
	ft_add_token_element(token_list,L_WORD, word->str);
	cmd = cmd + word->nb;
	free(word->str);
	free(word);
	return (cmd);
}

t_list	*ft_lexer(char *cmd, char **envtab)
{

	char	*temp_cmd;
	t_list	*token_list;

	token_list = NULL;
	temp_cmd = cmd;
	while (*temp_cmd)
	{
	       if (*temp_cmd == ' ')
		       temp_cmd++;
	       else if (*temp_cmd == '|')
	       {
	       	       ft_add_token_element(token_list, L_PIPE, "|");
		       temp_cmd++;
	       }
	       else if (*temp_cmd == '>' || *temp_cmd == '<')
		       temp_cmd = ft_handle_redir(temp_cmd, token_list);
	       else
		       temp_cmd = ft_add_word(temp_cmd,token_list, envtab);
	}
	return (token_list);
}

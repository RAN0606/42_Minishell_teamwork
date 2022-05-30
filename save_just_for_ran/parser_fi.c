/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/27 19:47:19 by rliu             ###   ########.fr       */
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

int ft_check_envvalue(char *keyequal, char **envtab) // check if the keyword is exit
{
	int	i;

	i = 0;
	while (*(envtab + i))
	{
		if (!ft_strncmp(envtab[i], keyequal, ft_strlen(keyequal)))
				return (i);
		i++;
	}
	return (-1);
}

int ft_check_envkey(char *cmd)
{
	int	i;
	
	i = 0;
	while (cmd[++i])
		if (cmd[i] == ' ' || cmd[i] == '"' || cmd[i] =='\'' )
			return (i);
	return (i);
}

char *ft_return_envvalue(char *key, char **envtab)
{
	char	*keyequal;
	int 	index;

		
	keyequal = ft_strjoin(key, "=");
	index = -2;
	index = ft_check_envvalue(key, envtab);
	if (index >= 0)
	{
		//printf("%d test: %s", index,envtab[index]+ ft_strlen(keyequal));
		return (ft_strdup(envtab[index] + ft_strlen(keyequal)));
	}
	return (ft_strdup(""));
}

char	*ft_dollar_inword(char *temp_cmd, char **envtab, t_word *word)
{
	char	*env_key;
	char	*env_value;
	int	j;
	
	j = 0;
	if(*(temp_cmd + 1) =='\'')
		return (temp_cmd + 1);
	j = ft_check_envkey(temp_cmd);
	if (j == 1)
		word->str = ft_strjoinfree(word->str, ft_strdup("$"));
	else
	{
		env_key = ft_substr(temp_cmd, 1, j-1);
		env_value = ft_return_envvalue(env_key, envtab);
		free(env_key);
		word->str = ft_strjoinfree(word->str, env_value);
	}	
	return (temp_cmd + j);	
}

int	ft_chr_quote(char *cmd, char c)
{
	int	i;
	
	i = 0;
	while (cmd[++i])
	{
		if (cmd[i] == c)
			return (i);
	}
	return (-1);		
}


char	*ft_handle_dollar(char *cmd, char **envtab)
{
	char	*env_key;
	char	*env_value;
	int	j;

	j = ft_check_envkey(cmd);
	if (j == 1)
	{
		return (ft_strdup("$"));
	}
	else if (j > 1)
	{
		env_key = ft_substr(cmd, 1, j - 1);
		env_value = ft_return_envvalue(env_key, envtab);
		free(env_key);
		return (env_value);
	}	
	return (0);	
}

char	*ft_return_quotevalue(char *cmd, char c, char **envtab)
{
	int	i;
	char	*str;

	str = ft_strdup("");
	i = -1;
	while (cmd[++i] != c)
	{
		if (cmd[i] == '$' && c =='\"')
		{	
			str = ft_strjoinfree(str, ft_handle_dollar(cmd, envtab));
			i = ft_check_envkey(cmd) - 1;
		}
		else 
			str = ft_strjoinfree(str, ft_substr(cmd, i, 1));
	}
	return (str);
}

char *ft_handle_quote (char *temp_cmd, t_word *word, char **envtab)
{
	int j;

	j = ft_chr_quote(temp_cmd, *temp_cmd);
	if (j < 0)
	{
		printf("parsing error: quote is not closed (don't need to do it - 42 subject)");
		return (NULL);
	}
	else
		word->str = ft_strjoinfree(word->str, ft_return_quotevalue(temp_cmd + 1, *temp_cmd, envtab));
	return (temp_cmd + j + 1);
}

int	ft_check_signe(char c)
{
	if (c ==' ' || c =='<' || c == '>' )
		return (1);
	return (0);
}

t_word	*ft_readword(char *temp_cmd, char **envtab)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->str = ft_strdup("");
	while (*temp_cmd && !ft_check_signe(*temp_cmd))
	{
		if (*temp_cmd == '\'' || *temp_cmd== '"')
			temp_cmd = ft_handle_quote(temp_cmd, word, envtab);
		else if (*temp_cmd == '$')
			temp_cmd = ft_dollar_inword(temp_cmd, envtab, word);
		else
			word->str = ft_strjoinfree(word->str, ft_substr(temp_cmd++, 0, 1));			
	}
	word->ptr_cmd = temp_cmd;
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

int	ft_add_token_element(t_list **token_list, int token, char *str)
{
	t_list	*token_element;

	token_element = ft_token(token, str);
	if (!token_element)
	{
		ft_lstclear(token_list,ft_free_token);
		return (0);
	}
	ft_lstadd_back(token_list, token_element);
	return (1);
}

char	*ft_handle_redir(char *cmd, t_list **token_list)
{
	if (*cmd == '>')
	{
		if (*++cmd == '>')
			ft_add_token_element(token_list,L_APPEND,">>");
		else
			ft_add_token_element(token_list,L_OUTPUT,">");
	}
	else if (*cmd == '<')
	{
		if (*++cmd == '<')
			ft_add_token_element(token_list,L_HEREDOC,"<<");
		else
		
			ft_add_token_element(token_list,L_INPUT, "<");
	}
	return (cmd);
}


char	*ft_add_word(char *cmd, t_list **token_list, char **envtab)
{
	t_word	*word;
	
	word = ft_readword(cmd, envtab);
	if (!word)
	{
		ft_lstclear(token_list, ft_free_token);
		return 0;
	}
	ft_add_token_element(token_list,L_WORD, word->str);
	cmd = word->ptr_cmd;
	free(word->str);
	free(word);
	return (cmd);
}

t_list	*ft_lexer(char *cmd, char **envtab)
{

	char	*temp_cmd;
	t_list	*token_list;

	token_list = NULL;
	temp_cmd = cmd - 1;
	while (*++temp_cmd)
	{
	       if (*temp_cmd == ' ')	
		       continue ;
	       else if (*temp_cmd == '|')	       
		       ft_add_token_element(&token_list, L_PIPE, "|");	
	       else if (*temp_cmd == '>' || *temp_cmd == '<')
		       temp_cmd = ft_handle_redir(temp_cmd, &token_list);
	       else
		       temp_cmd = ft_add_word(temp_cmd, &token_list, envtab);
	}
	return (token_list);
}

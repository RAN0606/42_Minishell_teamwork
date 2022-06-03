/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/26 16:42:14 by rliu             ###   ########.fr       */
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

int	ft_chr_quote(char *cmd, char c)
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
	j = ft_chr_quote(cmd, c);
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
			j = ft_chr_quote(temp_cmd + i + 1, temp_cmd[i]);
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

t_list	*ft_lexer(char *cmd, char **envtab)
{

	char	*temp_cmd;
	int	i;
	t_word	*word;
	t_list	*token_element;
	t_list	*token_list;

	token_list = NULL;
	token_element = NULL;
	i = 0;	
	temp_cmd = ft_strtrim(cmd," ");
	while (temp_cmd[i])
	{
	       if (temp_cmd[i] == ' ')
		       i++;	
	       else if (temp_cmd[i] == '|')
	       {
		      token_element = ft_token(L_PIPE, "|");
		      if (!token_element)
		      {
			      ft_lstclear(&token_list,ft_free_token);
			      return (NULL);
		      }
		      ft_lstadd_back(&token_list, token_element);
		     // printf("%c\n", temp_cmd[i]);
		      i++;
	       }
	       else if (temp_cmd[i] == '>')
	       {
		      if (temp_cmd[++i] == '>')
		      {
			      token_element = ft_token(L_APPEND, ">>");
			      i++;
		      }
		      else
			      token_element = ft_token(L_INPUT, ">");
		      if (!token_element)
		      {
			      ft_lstclear(&token_list,ft_free_token);
			      return (NULL);
		      }
		      ft_lstadd_back(&token_list, token_element);
		     // printf("%c\n", temp_cmd[i]);
	       }
	       else if (temp_cmd[i] == '<')
	       {

		      token_element = ft_token(L_OUTPUT, "<");
		      if (!token_element)
		      {
			      ft_lstclear(&token_list,ft_free_token);
			      return (NULL);
		      }
		      ft_lstadd_back(&token_list, token_element);
		     // printf("%c\n", temp_cmd[i]);
		      i++;
	       }
	       else
	       {
		       word = ft_readword(temp_cmd + i, envtab);
		       if (!word)
		       {
			       ft_lstclear(&token_list, ft_free_token);
			       return 0;
		       }
		      token_element = ft_token(L_WORD, word->str);
		      if (!token_element)
		      {
			      ft_lstclear(&token_list,ft_free_token);
			      return (NULL);
		      }
		       ft_lstadd_back(&token_list, token_element);
		      // printf("%s\n", word->str);
		       i = i + word->nb;
		       free(word->str);
		       free(word);
	       }
	}
	return (token_list);
}
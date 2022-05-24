/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/24 13:15:28 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum token {L_WORD, L_PIPE, L_INPUT, L_OUTPUT, L_APPEND, L_HEREDOC};

typedef struct s_token
{
	int	token;
	char	*cmd;
}t_token;

typedef struct s_word
{
	char	*str;
	int	nb;
}t_word;


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

int ft_check_envvalue(char *key, char **envtab) // check if the keyword is exit
{
	int	i;
	char	*keyequal;

	i = 0;
	while (*(envtab + i))
	{
		if (!ft_strncmp(envtab[i], keyequal, ft_strlen(keyequal)))
				return (i);
		i++;
	}
	return (-1);
}

char *ft_return_envvalue(char *key, char **envtab)
{
	char	*keyequal;
	int 	index;

		
	keyequal = ft_strjoin(key, "=");
	index = -2;
	index = ft_checkenv(key, envtab);
	else if (index >= 0)
		return (ft_strdup(envtab[index] + ft_strlen(keyequal));
	return(ft_strdup(""));
}

int ft_check_envkey(char *cmd, i)
{
	while (cmd[i])
	{
		if (temp_cmd[i] == ' ')
			return (i-1);
		i++;
	}
	return (i-1);
}

char	*ft_handle_dollar(char *cmd, i, char **envtab)
{
	char	*env_key;
	char	*env_value;
	int	j;

	j = ft_check_envkey(cmd, i + 1);
	if (j == i)
		return (0);
	if (j > i)
	{
		env_key = ft_substr(cmd, i + 1, j - i);
		env_value = ft_return_envvalue(env_key, envtab);
		return (env_value);
	}	
	return (0)	
}

int	ft_chr_quote(char *cmd, char c)
{
	int	i;
	i = -1;

	while (*(cmd + (++i)))
	{
		if (*(cmd+i) == c)
			return (i);
	}
	return (-1);
		
}

t_word	*ft_readword(char *cmd)
{
	int	i;
	int	j;
	char	*temp_cmd;
	t_word	*word;
	char	*env_value;

	i=0;
	j=-1;	
	temp_cmd = ft_strtrim(cmd," ");
	free(cmd);
	word = malloc(sizeof(t_word));
	word->str = ft_strdup("");
	while (temp_cmd[i])
	{
		if (temp_cmd[i] == '\'' || temp_cmd[i] == '"')
		{
			j = ft_chr_quote(temp_cmd + i + 1, temp_cmd[i]);
			if (j < 0)
			{
				printf("parsing error: quote is not cloesed!\n");
				free(temp_cmd);
				return (NULL);
			}
			word->str = ft_strjoinfree(word->str, ft_substr(temp_cmd, i + 1, j));
			i = i + 2 + j;
		}
		if (temp_cmd[i] == '$')
		{
			env_value = ft_handle_dollar(temp_cmd, i);
			if (env_value)
				printf("%s\n", env_value)
			
		}
		else if (temp_cmd[i] ==' ')
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


void ft_lexer(char *cmd)
{

	char	*temp_cmd;
	int	i;
	t_word	*word;

	i = 0;
	temp_cmd = cmd;
	while (temp_cmd[i])
	{
	       if (temp_cmd[i] == ' ')
		       i++;	
	       else if (temp_cmd[i] == '|')
	       {
		       printf("there is a pipe\n");
		       i++;
	       }
	       else if (temp_cmd[i] == '<' || temp_cmd[i] == '>')
	       {
		       printf("there is a redirection\n");
		       i++;
	       }
	       else
	       {
		       word = ft_readword(temp_cmd + i);
		       printf("%s\n", word->str);
		       i = i + word->nb;
		       free(word->str);
		       free(word);
	       }
	}
}

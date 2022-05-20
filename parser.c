/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/20 18:33:07 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*enum token {L_WORD, L_PIPE, L_INPUT, L_OUTPUT, L_APPEND, L_HEREDOC};

typedef struct s_token
{
	char	*cmd;
	int	token;
}*/

char *ft_chr_quote(char *cmd_ptr)
{
	int	i;
	i = -1;

	while (*(cmd + (++i)))
		if (*(cmd+i) == ''')
			return(ft_substr());
	return (-1);
		
}
t_list *ft_lexer(char *cmd)
{
//	t_list *lexer_list;
	int	i;
	int	j;
	char	*temp_cmd;
	char	*word;

	i=0;
	j=-1;
	temp_cmd = ft_strtrim(cmd," ");
	word = ft_strdup("");
	while (temp_cmd[i])
	{
		if(*(temp+i) == ''')
		{
			j = ft_paire_quote(cmd + i + 1);
			if (j < 0)
			{
				printf("parsing error: quote is not cloesed!");
				free(cmd);
				return (0);
			}
		}
	}
	printf("%s", cmd);
	printf("%s", temp);
	free(cmd);
	free(temp);
	return (0);
	
}

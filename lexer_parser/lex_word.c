/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:18 by rliu              #+#    #+#             */
/*   Updated: 2022/05/27 20:57:46 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (*temp_cmd && !ft_check_signe(*temp_cmd) && temp_cmd)
	{
		if (*temp_cmd == '\'' || *temp_cmd== '"')
			temp_cmd = ft_handle_quote(temp_cmd, word, envtab);
		else if (*temp_cmd == '$')
			temp_cmd = ft_dollar_inword(temp_cmd, envtab, word);
		else
			word->str = ft_strjoinfree(word->str, ft_substr(temp_cmd++, 0, 1));			
	}
	if (!temp_cmd)
		return(NULL);
	word->ptr_cmd = temp_cmd;
	return (word);
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

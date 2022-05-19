/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:53:57 by rliu              #+#    #+#             */
/*   Updated: 2022/05/19 15:46:48 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
enum token{MS_PIPE, MS_INPUT, MS_OUTPUT, MS_APPEND,MS_HEREDOC};
typedef struc s_cmd_lexer
{
	char	*word;
	int	token;
}t_cmd_lexer;



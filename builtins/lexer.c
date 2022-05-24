/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:18:57 by qxia              #+#    #+#             */
/*   Updated: 2022/05/23 16:28:50 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token new_token(char *value, int id)
{
    t_token *token;
    
    token = malloc(sizeof(*token));
    token->value = ft_strdup(value);
    token->id = id;
    return (token);    
}

t_list  *get_token(char *s)
{
    
}
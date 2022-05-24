/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:04:35 by qxia              #+#    #+#             */
/*   Updated: 2022/05/24 14:52:29 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void error_print(char *args)
{
    ft_putstr_fd("Minishell: unset: ", 2);
    ft_putstr_fd(args, 2);
    ft_putstr_fd(": \'not a valid identifier\'\n", 2);
    return ;  
}

static size_t   size_env(char   *env)
{
    size_t  i;

    i = 0;
    while(env[i] && env[i] != '=')
        i++;
    return (i);
}

static void free(t_env *env, t_mini *mini)
{
    ??ft_memdel(env);
}

int ft_unset(char   **args, t_mini  *mini)
{
    t_env   *env;
    t_env   *tmp;

    env = mini->env;
    if (!args[1])
        return (0);
    if (ft_strcmp(args[1], env->value) == 0)
    {
        free ??;
        return (0);
    }
    while (env && env->next)
    {
        if (ft_strcmp(args[1], env->next->value) == 0)
        {
            tmp = env->next->next;
            free ??;
            env->next = tmp;
            return (0);
        }
        env = env->next;
    }
    return (0);
}
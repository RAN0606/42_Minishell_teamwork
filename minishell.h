/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:55:21 by rliu              #+#    #+#             */
/*   Updated: 2022/05/16 11:51:53 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

# define BUFFER_SIZE 10000

int	ft_pwd(void);

#endif

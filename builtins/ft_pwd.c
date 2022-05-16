/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:23:17 by qxia              #+#    #+#             */
/*   Updated: 2022/05/16 11:23:35 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, BUFFER_SIZE);
	if (!str)
	{
		write(1, "getting cwd error\n",18);
		return (EXIT_FAILURE);
	}
	else
		printf("%s\n", str);
	free (str);
	return (EXIT_SUCCESS);
}

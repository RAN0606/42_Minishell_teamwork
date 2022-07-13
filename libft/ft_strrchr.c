/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:19:06 by rliu              #+#    #+#             */
/*   Updated: 2021/11/29 19:00:00 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*strtermi;
	unsigned int	size;

	size = ft_strlen(str) + 1;
	strtermi = (char *)str + ft_strlen(str);
	while (size-- > 0)
	{
		if (*strtermi == (char)c)
			return (strtermi);
		strtermi--;
	}
	return (0);
}

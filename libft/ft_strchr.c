/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:09:27 by rliu              #+#    #+#             */
/*   Updated: 2021/11/30 15:27:02 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char			*strtemp;
	unsigned int	size;

	strtemp = (char *)str;
	size = ft_strlen(str) + 1;
	while (size-- > 0)
	{
		if (*strtemp == (char)c)
			return (strtemp);
		strtemp++;
	}
	return (0);
}

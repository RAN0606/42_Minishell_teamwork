/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:10:37 by rliu              #+#    #+#             */
/*   Updated: 2021/11/30 17:02:06 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t	size)
{
	size_t	i;
	size_t	j;
	size_t	compt;

	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	compt = i + ft_strlen(src);
	while (i + 1 < size && src [j] && size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (i < size)
		dest[i] = '\0';
	return (compt);
}

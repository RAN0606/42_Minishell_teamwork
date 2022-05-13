/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:27:48 by rliu              #+#    #+#             */
/*   Updated: 2021/11/29 15:10:16 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void*src, size_t len)
{
	unsigned char	*dsttemp;

	dsttemp = (unsigned char *)dst;
	if (dst < src)
	{
		while (len-- > 0)
			*dsttemp++ = *(unsigned char *)src++;
	}
	if (dst > src)
	{
		while (len-- > 0)
			*(dsttemp + len) = *((unsigned char *)src + len);
	}
	return (dst);
}

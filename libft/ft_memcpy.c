/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:13:44 by rliu              #+#    #+#             */
/*   Updated: 2021/12/06 20:38:28 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t len)
{
	unsigned char	*dsttemp;

	if (!dst && !src)
		return (0);
	dsttemp = (unsigned char *)dst;
	while (len-- > 0)
		*(unsigned char *)dsttemp++ = *(unsigned char *)src++;
	return (dst);
}
/*
#include <libc.h>
#include <string.h>
int	main()
	
{
	char	src[12]="12345678900";
	char	dest[12]= "aaaaaaaaaaa";

	ft_memcpy(dest, src, 9);
	printf("%s\n%s", src, dest);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:39:38 by rliu              #+#    #+#             */
/*   Updated: 2021/11/29 13:22:12 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *src1, const void *src2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)src1++;
	s2 = (unsigned char *)src2++;
	while (n-- > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
/*
int	main()
{
	int	array1[10] = {1,2,3,4,5,6,7};
	int	array2[10] = {1,2,3,4,5,6,7};
	char	string1[11] ="1234567890";
	char	string2[11] ="0236123458";

	printf("memcmp %d %d \n", memcmp(), memcmp());
	printf("ft_memcmp %d %d \n", ft_memcmp(), ft_memcmp());
}
*/

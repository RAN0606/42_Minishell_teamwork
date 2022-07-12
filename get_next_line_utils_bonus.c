/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:54:24 by rliu              #+#    #+#             */
/*   Updated: 2021/12/20 20:12:36 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	ft_bzero(void *s, int n)
{
	char	*string;

	string = s;
	if (n == 0)
		return ;
	while (n > 0)
	{
		*string++ = 0;
		n--;
	}
}

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

size_t	ft_strlen(const	char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s;
	int		i;

	if (!s1 || !s2)
		return (0);
	s = (char *)malloc(sizeof(*s) * ((ft_strlen(s1) + (ft_strlen(s2) + 1))));
	if (!s)
		return (0);
	i = 0;
	while (*s1)
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}

char	*ft_strdup(const char *s1)
{
	char		*dest;
	long int	n;

	n = (ft_strlen(s1) + 1) * sizeof(char);
	dest = (char *) malloc (n);
	if (!dest)
		return (0);
	return (ft_memcpy(dest, s1, n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:27:21 by rliu              #+#    #+#             */
/*   Updated: 2021/12/06 21:43:43 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_sizeint(int n)
{
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		i = 1;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*stritoa;
	size_t	len;

	len = ft_sizeint(n);
	stritoa = (char *)malloc((len + 1) * sizeof(char));
	if (!stritoa)
		return (0);
	if (n == -2147483648)
	{
		ft_strlcpy(stritoa, "-2147483648", 12);
		return (stritoa);
	}
	stritoa[len] = '\0';
	if (n < 0)
	{
		n = -n;
		stritoa[0] = '-';
	}
	while (n >= 10)
	{
		stritoa[--len] = n % 10 + '0';
		n = n / 10;
	}
	stritoa[--len] = n % 10 + '0';
	return (stritoa);
}

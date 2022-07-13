/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:47:05 by rliu              #+#    #+#             */
/*   Updated: 2021/12/06 21:41:27 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*dest;
	long int	n;

	n = (ft_strlen(s1) + 1) * sizeof(char);
	dest = (char *)malloc(n);
	if (!dest)
		return (0);
	return (ft_memcpy(dest, s1, n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:16:17 by rliu              #+#    #+#             */
/*   Updated: 2021/12/06 21:53:07 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	size_t	len;
	size_t	i;

	if (!s1 || !set)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	while (i < len && ft_strchr(set, (int)s1[i]))
		i++;
	while (len > i && ft_strchr(set, (int)s1[len - 1]))
		len--;
	len = len - i;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	ft_strlcpy(s, s1 + i, len + 1);
	return (s);
}

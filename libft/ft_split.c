/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:44:40 by rliu              #+#    #+#             */
/*   Updated: 2021/12/06 22:03:22 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_splitlen(char const *s, char c)
{
	size_t	x;

	x = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
			s++;
		x++;
	}
	if (*(s - 1) == c)
		x--;
	return (x);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**tabchar;

	tabchar = (char **) malloc((ft_splitlen(s, c) + 1) * sizeof(char *));
	if (!tabchar)
		return (0);
	index = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		while (i < ft_strlen(s) && s[i] == c)
			i++;
		j = 0;
		while (i + j < ft_strlen(s) && s[i + j] != c)
			j++;
		if (j > 0)
			tabchar[index++] = ft_substr(s, i, j);
		i = i + j;
	}
	tabchar[index] = 0;
	return (tabchar);
}

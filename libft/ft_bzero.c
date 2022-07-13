/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:00:52 by rliu              #+#    #+#             */
/*   Updated: 2021/11/29 12:51:20 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
/*#include <libc.h>
#include <string.h>
int	main()
{
	int	x[10];
	int n;

	n = 9;
	while (n >= 0)
	{
		x[n] = n;
		printf("%d \n",x[n]);
		n--;
	}
	ft_bzero(x, 50);
	n = 9;
	while (n >= 0)
	{
		printf("%d \n",x[n]);
		n--;
	}

}*/

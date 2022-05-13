/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:12:49 by rliu              #+#    #+#             */
/*   Updated: 2021/12/06 21:39:54 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	void			*ptr2;
	int				n;

	n = size * count;
	ptr = malloc(n);
	if (!ptr)
		return (0);
	ptr2 = ptr;
	while (n-- > 0)
		*ptr++ = 0;
	return (ptr2);
}
/*int	main()
{
	int	*a;
	int	i;
	
	i = 0;
	a =(int*)ft_calloc(11,sizeof(int));
	while(i < 11)
	{
		printf("%d\n",a[i]);
		i++;
	}
	free(a);
}
*/

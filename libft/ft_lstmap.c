/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 23:17:17 by rliu              #+#    #+#             */
/*   Updated: 2021/12/07 10:34:19 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*alst;
	t_list	*newel;

	if (!lst || !f)
		return (0);
	newel = ft_lstnew(f(lst->content));
	alst = newel;
	if (!newel)
		ft_lstclear(&lst, del);
	while (lst->next)
	{
		lst = lst->next;
		newel = ft_lstnew(f(lst->content));
		if (!newel)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&alst, del);
		}
		else
			ft_lstadd_back(&alst, newel);
	}
	return (alst);
}

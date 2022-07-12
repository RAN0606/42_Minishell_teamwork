/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:24:15 by rliu              #+#    #+#             */
/*   Updated: 2021/12/20 21:02:34 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <libc.h>

void	ft_bzero(void *s, int n);
void	*ft_memcpy(void	*dst, const void *src, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(const char *s1, char	const *s2);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);

#endif

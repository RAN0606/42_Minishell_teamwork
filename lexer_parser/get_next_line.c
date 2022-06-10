/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:54:24 by rliu              #+#    #+#             */
/*   Updated: 2022/02/21 11:33:55 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "checker.h"

size_t	get_size(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(buffer))
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*get_n(char *buffer)
{
	size_t	i;
	char	*line;
	char	dest [BUFFER_SIZE + 2];

	i = 0;
	while (i < ft_strlen(buffer))
	{
		if (buffer[i] == '\n')
		{
			line = (char *)malloc((i + 2) * sizeof(char));
			if (!line)
				return (0);
			ft_memcpy(line, buffer, i + 1);
			line[i + 1] = '\0';
			ft_memcpy(dest, buffer, BUFFER_SIZE + 1);
			ft_bzero(buffer, BUFFER_SIZE + 1);
			ft_memcpy(buffer, dest + i + 1,
				BUFFER_SIZE - i - 1);
			return (line);
		}
		i++;
	}
	return (0);
}

char	*get_join(char *buffer, int fd)
{
	char	*line;
	char	*lineplus;
	char	dest[BUFFER_SIZE + 2];

	ft_memcpy(dest, buffer, BUFFER_SIZE + 1);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	line = get_next_line(fd);
	if (!line)
		return (ft_strdup(dest));
	lineplus = ft_strjoin(dest, line);
	free(line);
	return (lineplus);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!*buffer)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			return (0);
	}
	if (get_size(buffer))
		return (get_n(buffer));
	else
		return (get_join(buffer, fd));
	return (0);
}

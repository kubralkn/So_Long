/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:09 by kalkan            #+#    #+#             */
/*   Updated: 2024/12/06 15:29:01 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_update_stash(char *stash)
{
	int		i;
	int		j;
	char	*s1;

	j = 0;
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	s1 = f_calloc(((ft_len(stash) - i)), sizeof(char));
	if (!s1)
		return (NULL);
	i++;
	while (stash[i] != '\0')
	{
		s1[j] = stash[i];
		j++;
		i++;
	}
	free(stash);
	return (s1);
}

char	*ft_before_nl(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = f_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	while (j <= i && stash[j] != '\0')
	{
		line[j] = stash[j];
		j++;
	}
	return (line);
}

char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		count;

	buffer = f_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	count = 1;
	while (!f_strchr(buffer) && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (free(buffer), NULL);
		buffer[count] = '\0';
		stash = f_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (free(stash), stash = NULL, NULL);
	line = ft_before_nl(stash);
	stash = ft_update_stash(stash);
	return (line);
}

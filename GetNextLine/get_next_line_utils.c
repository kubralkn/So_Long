/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:07 by kalkan            #+#    #+#             */
/*   Updated: 2024/12/06 15:37:16 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_len(const char *stash)
{
	int	i;

	i = 0;
	while (stash[i] != '\0')
		i++;
	return (i);
}

char	*f_calloc(int count, int size)
{
	int		i;
	int		result;
	char	*str;

	i = 0;
	result = count * size;
	str = (char *)malloc(result);
	if (!str)
		return (0);
	while (result > 0)
	{
		str[i] = 0;
		i++;
		result--;
	}
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(ft_len(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*f_strjoin(char *stash, char *buffer)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	if (!stash && buffer)
	{
		stash = ft_strdup(buffer);
		return (stash);
	}
	dst = (char *)malloc(((ft_len(stash) + ft_len(buffer)) * sizeof(char)) + 1);
	if (!dst)
		return (0);
	while (stash[i])
	{
		dst[i] = stash[i];
		i++;
	}
	while (buffer[j] != '\0')
		dst[i++] = buffer[j++];
	dst[i] = '\0';
	free(stash);
	return (dst);
}

int	f_strchr(const char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

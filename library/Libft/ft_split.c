/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:11:51 by kalkan            #+#    #+#             */
/*   Updated: 2024/11/03 13:12:38 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	split_word_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += word_len(s, c);
		}
		else
			s++;
	}
	return (count);
}

static void	*free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**new_str;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = split_word_count(s, c);
	new_str = malloc(sizeof(char *) * (count + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			new_str[i] = ft_substr(s, 0, word_len(s, c));
			if (!new_str[i++])
				return (free_str(new_str));
			s += word_len(s, c);
		}
		else
			s++;
	}
	new_str[i] = NULL;
	return (new_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:31:01 by kalkan            #+#    #+#             */
/*   Updated: 2024/10/26 15:38:27 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	char	*result;

	s_len = ft_strlen(s);
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= s_len || s_len == 0 || len == 0)
		return (ft_strdup(""));
	while (i < len && s[i + start])
		i++;
	result = (char *) malloc((sizeof(char) * i) + 1);
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = s[start + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

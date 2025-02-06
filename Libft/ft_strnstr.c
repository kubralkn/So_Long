/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:30 by kalkan            #+#    #+#             */
/*   Updated: 2024/11/02 11:28:56 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t	len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (*haystack && len--)
	{
		i = 0;
		while (haystack[i] == needle[i])
		{
			if (!needle[++i])
				return ((char *)haystack);
			if (i > len)
				return (0);
		}
		haystack++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:19:23 by kalkan            #+#    #+#             */
/*   Updated: 2024/10/26 15:19:25 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = 0;
	if (!dstsize)
		return (srclen);
	if (dstsize < dstlen)
		return (srclen + dstsize);
	while (src[i] && i < dstsize - dstlen)
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	if (i == dstsize - dstlen && dstsize > dstlen)
		i--;
	dst[i + dstlen] = '\0';
	return (srclen + dstlen);
}

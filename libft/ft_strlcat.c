/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:16:38 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/19 21:52:32 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	i = ft_strlen(dst);
	j = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (size < dstlen)
		return (srclen + size);
	else
	{
		while (src[j] && (dstlen + j) < size)
			dst[i++] = src[j++];
		if ((dstlen + j) == size && dstlen < size)
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (srclen + dstlen);
	}
}

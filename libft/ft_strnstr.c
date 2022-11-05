/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:54:39 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/25 16:08:00 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	size_t	i;
	size_t	j;

	j = 0;
	h = (char *)haystack;
	if (needle[0] == 0)
		return (h);
	while (h[j] != '\0' && j < len)
	{
		i = 0;
		while (h[j + i] == needle[i] && h[j + i] != '\0' && i + j < len)
			i++;
		if (needle[i] == '\0')
			return (&h[j]);
		j++;
	}
	return (NULL);
}

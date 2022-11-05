/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:24:39 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/07 16:30:11 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(count * size);
	if (!dst)
		return (NULL);
	while (i < count * size)
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}

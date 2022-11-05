/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:21:29 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/11 21:35:22 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dt;
	unsigned char	*sc;
	size_t			i;

	dt = (unsigned char *)dst;
	sc = (unsigned char *)src;
	i = 0;
	if (sc == dt)
		return (dst);
	if (dt > sc)
	{
		while (len--)
			dt[len] = sc[len];
	}
	else
	{
		while (i < len)
		{
			dt[i] = sc[i];
			i++;
		}
	}
	return (dst);
}

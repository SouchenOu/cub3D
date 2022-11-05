/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:39:55 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/05 20:58:33 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
		{
			ptr = (char *) s;
		}	
		s++;
	}
	if (*s == (unsigned char)c)
	{
		ptr = (char *) s;
	}
	return (ptr);
}

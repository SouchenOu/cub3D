/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:35:11 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/20 15:54:49 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char str, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (str == set[i])
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	char	*str;
	char	*start;
	int		len;
	int		i;

	i = 0;
	str = (char *)s1;
	start = (char *)set;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && ft_check(str[i], start))
			i++;
	if (len == i)
		return (ft_strdup(""));
	while (s1[i] && ft_check(str[len - 1], start))
		len--;
	dst = (char *)malloc(((len - i) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, &str[i], (len - i) + 1);
	return (dst);
}

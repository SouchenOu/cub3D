/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:34:18 by yismaili          #+#    #+#             */
/*   Updated: 2021/11/20 17:05:47 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lt;
	t_list	*tmp;

	lt = *lst;
	while (lt)
	{
		tmp = lt->next;
		ft_lstdelone(lt, del);
		lt = tmp;
	}
	*lst = NULL;
}

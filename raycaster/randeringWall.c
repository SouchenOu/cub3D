/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randeringWall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:51:18 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/22 20:02:47 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	degrees_to_radians(double a)
{
	return ((a * 3.14159265359) / 180);
}
int	is_ceiling(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (--i > -1)
	{
		if (buffer[i][k] != 0)
			return (0);
	}
	return (1);
}

int	is_floor(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (++i < W_HEIGHT)
	{
		if (buffer[i][k] != 0)
			return (0);
	}
	return (1);
}

void ft_colorBuffer(t_struct *cub)
{
    int i;
    int k;
    i = 0;
	while (i < W_HEIGHT)
	{
		k = 0;
		while (k < W_WIDTH)
        {
            cub->color_buffer[i][k] = 0;
            k++;
        }
        i++;
	}
    cub->check_test = 0;
}
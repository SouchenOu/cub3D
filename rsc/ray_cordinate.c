/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cordinate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:42 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ray_cordinate(t_ray *raycast, int direction)
{
	if (direction == 'v')
	{
		if (raycast->virt_cord.x > 0 && raycast->virt_cord.x > 0)
		{
			raycast->ray_cordinate.x = raycast->virt_cord.x;
			raycast->ray_cordinate.y = raycast->virt_cord.y;
		}
		else
		{
			raycast->ray_cordinate.x = raycast->horizontal_cord.x;
			raycast->ray_cordinate.y = raycast->horizontal_cord.y;
		}
	}
	else if (direction == 'h')
	{
		if (raycast->horizontal_cord.x > 0 && raycast->horizontal_cord.y> 0)
		{
			raycast->ray_cordinate.x = raycast->horizontal_cord.x;
			raycast->ray_cordinate.y = raycast->horizontal_cord.y;
		}
		else
		{
			raycast->ray_cordinate.x = raycast->horizontal_cord.x;
			raycast->ray_cordinate.y = raycast->horizontal_cord.y;
		}
	}
}
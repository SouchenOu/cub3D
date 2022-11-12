/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/12 18:15:58 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

double	degrees_to_radians(double a)
{
	return ((a * 3.14159265359) / 180);
}

double	limite_angle(double a)
{
	if (a > 359)
	{
		a = a - 360;
	}
	else if (a < 0)
	{
		a = a + 360;
	}
	return (a);
}
//pythagorean rule to calculate the length of the line between two points. 
double	pyt(double x1, double x2, double y1, double y2)
{
	return (sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1))));
}
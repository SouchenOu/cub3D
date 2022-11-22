/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 11:32:13 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/**Hence, from the above equation, we can say, 180 degrees is equal to π radian.
Usually, in general geometry, we consider the measure of the angle in degrees (°). Radian is commonly considered while measuring the angles of trigonometric functions or periodic functions. Radians is always represented in terms of pi, where the value of pi is equal to 22/7 or 3.14.*/

#include "../include/cub3D.h"

double	degrees_to_radians(double a)
{
	return ((a * 3.14159265359) / 180);
}


double	limite_angle(double a)
{
	if (a > 359.00)
	{
		a = a - 360.00;
	}
	else if (a < 0.00)
	{
		a = a + 360.00; // 2PI
	}
	return (a);
}

double	pythg(double x1, double x2, double y1, double y2)
{
	return (sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1))));
}
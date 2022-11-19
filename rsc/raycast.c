/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/19 03:26:19 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/**Ray-casting is a technique that transform a limited 
 * form of data (a very simplified map or floor plan) into a 3D projection 
 * by tracing rays from the view point into the viewing volume*/


void	lets_do_raycast(t_ray *raycast, int j)
{
	double	sostra;
	int		i;
	int		wallBottomPixel ;
	int		wallTopPixel;

	sostra = degrees_to_radians(raycast->cub->p.vect.pos) - raycast->ray_looking_angle;
	//printf("hadi = %f\n", raycast->ray_looking_angle);
	//printf("soustra = %f\n", sostra);
	if (sostra > degrees_to_radians(360))
		sostra -= degrees_to_radians(360);
	else if (sostra < degrees_to_radians(0.00))
		sostra += degrees_to_radians(360.00);
	raycast->final_distance = raycast->final_distance * cos(sostra);
	raycast->wallStripHeight= (int)(size_GRID * (1.00 * W_HEIGHT)) / raycast->final_distance;
	if (raycast->wallStripHeight> (1.00 * W_HEIGHT))
		raycast->wallStripHeight= (1.00 * W_HEIGHT);
	//wallTopPixel is the top of the wall
	wallTopPixel = (W_HEIGHT/ 2) - (int)(raycast->wallStripHeight/ 2.00);
	if (wallTopPixel < 0)
		wallTopPixel = 0; // the minimum we can have is 0
		//wallBottomPixel is the Bottom or end of the wall
	wallBottomPixel = (W_HEIGHT/ 2) + (int)(raycast->wallStripHeight/ 2.00);
	if (wallBottomPixel >= W_HEIGHT)
		wallBottomPixel = W_HEIGHT - 1;
	i = (wallTopPixel - 1);
	//render the wall from wallTopPixel to wallBottomPixel
	while (i < wallBottomPixel)
	{
		//copy all the color buffer to an sdl texture
		raycast->cub->colorBuffer[i][j] = 0xFFF0000;
		raycast->cub->check = 1;
		i++;
	}
}


void	raycast(t_struct *cub)
{
	int	i;

    i = 0;
	
	

	ft_get_wall_cordinate(cub);

	while (i < cub->NB_rays)
	{
		printf("i = %d\n", i);
		check_vertical_horizontal(&cub->raycast[i]);
		ddaForLine(cub, cub->player.position_x, cub->player.position_y , cub->raycast->ray_cordinate.x, cub->raycast->ray_cordinate.y, 0xFFFF0F);
		
        i++;
		
	}
   
	
}

void ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color)
{
    // calculate dstnc_x & dstnc_y
    int dstnc_x = x_1 - x_0;
    int dstnc_y = y_1 - y_0;
 
    // calculate steps required for generating pixels
    int steps;
    if (abs(dstnc_x) > abs(dstnc_y))
        steps = abs(dstnc_x);
    else
        steps = abs(dstnc_y);
    // calculate increment in x & y for each steps
    float x_inc = dstnc_x / (float)steps;
    float y_inc = dstnc_y / (float)steps;
    // Put pixel for each step
    float x = x_0;
    float y = y_0;
    int i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += x_inc; // increment in x at each step
       y += y_inc; // increment in y at each step
       i++;
    }
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 15:46:35 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/**Ray-casting is a technique that transform a limited 
 * form of data (a very simplified map or floor plan) into a 3D projection 
 * by tracing rays from the view point into the viewing volume*/


void	lets_do_raycast(t_ray *raycast, int x)
{
	double	sostra;
	int		y;
	int		end;
	int		start;

	sostra = degrees_to_radians(raycast->cub->p.vect.pos) - raycast->ray_looking_angle;
	if (sostra > degrees_to_radians(359.00))
		sostra -= degrees_to_radians(360.00);
	else if (sostra < degrees_to_radians(0.00))
		sostra += degrees_to_radians(360.00);
	raycast->final_distance = raycast->final_distance * cos(sostra);
	raycast->h_line = (int)(size_GRID * (1.00 * W_HEIGHT)) / raycast->final_distance;
	if (raycast->h_line > (1.00 * W_HEIGHT))
		raycast->h_line = (1.00 * W_HEIGHT);
	start = (W_HEIGHT/ 2) - (int)(raycast->h_line / 2.00);
	if (start < 0)
		start = 0;
	end = (W_HEIGHT/ 2) + (int)(raycast->h_line / 2.00);
	if (end >= W_HEIGHT)
		end = W_HEIGHT- 1;
	y = (start - 1);
	while (++y < end)
	{
		raycast->cub->tab[y][x] = 0xFFF0000;
		raycast->cub->check = 1;
	}
}

/*The player should be able to see what is in front of him/her.
For this, we will need to define a field of view (FOV).
The FOV determines how wide the player sees the world in 
front of him/her */

/****To put the player inside the world, 
 * we need to define the player’s X coordinate, 
 * the player’s Y coordinate, and the angle that 
 * the player is facing to*/

//A projection plane of 320(width) units wide and 200 (height) units so think of 1 pixel as equal to 1 unit. //
void	raycast(t_struct *cub)
{
	int	i;
    //int j;
    i = 0;
	//double	sostra;
	int		y = 0;
	//int		end;
	//int		start;

	//t_ray raycast;

	/*we define the FOV to be 60 degrees through 
	trial and experimentation (on how good it looks
	 on screen)*/
	//cub->FOV = 60;
	//Dimension of the Projection Plane = W_WIDTH
	//cub->NB_rays =  W_WIDTH;
	//cub->looking_angle = 280 - ((double)cub->FOV / 2);
	//cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);

	// cast all nb_rays
	/*while (i < cub->NB_rays)
	{
		raycast.cub = cub;
		raycast.ray_looking_angle = degrees_to_radians(limite_angle(cub->looking_angle));
		raycast.ray_cordinate.x = -1;
		raycast.ray_cordinate.y = -1;
		raycast.offset.x = -1;
		raycast.offset.y = -1;
		raycast.dir = 0;
		raycast.number_to_check = -2;
		raycast.tang = 0;
		raycast.cub->p.cord.x = 100.00;
		//cub.p.cord.y = 220.00;
    	//cub.p.vect.x = cos(degrees_to_radians(280.00));
		//cub.p.vect.y = -sin(degrees_to_radians(280.00));
		raycast.horizontal_distance = 0;
		raycast.horizontal_cord.y = 0;
		raycast.horizontal_cord.x = 0;
		raycast.virt_cord.x = 0;
		raycast.virt_cord.y = 0;
		raycast.virtical_distance = 0;
        raycast.ray_cord_temp.x = 0;
        raycast.ray_cord_temp.y = 0;
		raycast.dest = 0;
		raycast.h_line = 0;

		
		cub->looking_angle = cub->looking_angle +  (cub->FOV / (double)cub->NB_rays);
        i++;
	}*/
    //start raycasting
	i = 0;
	if (cub->check == 1)
		ft_tab(cub);
	while (i < cub->NB_rays) // nb rays is the width of screen
	{
		check_horizontal_vertical(&cub->raycast[i]);
		//lets_do_raycast(&cub->raycast[i], i);
		/*sostra = degrees_to_radians(cub->raycast->cub->p.vect.pos) - cub->raycast->ray_looking_angle;
		if (sostra > degrees_to_radians(359.00))
			sostra -= degrees_to_radians(360.00);
		else if (sostra < degrees_to_radians(0.00))
			sostra += degrees_to_radians(360.00);
		cub->raycast->dest = cub->raycast->dest * cos(sostra);
		cub->raycast->h_line = (int)(size_GRID * (1.00 * W_HEIGHT)) / cub->raycast->dest;
		if (cub->raycast->h_line > (1.00 * W_HEIGHT))
			cub->raycast->h_line = (1.00 * W_HEIGHT);
		start = (W_HEIGHT/ 2) - (int)(cub->raycast->h_line / 2.00);
		if (start < 0)
			start = 0;
		end = (W_HEIGHT/ 2) + (int)(cub->raycast->h_line / 2.00);
		if (end >= W_HEIGHT)
			end = W_HEIGHT- 1;
		y = (start - 1);*/
		while (y < 100)
		{
			cub->raycast->cub->tab[y][i] = 0xFFF0000;
			cub->raycast->cub->check = 1;
			y++;
		}
       	 i++;
	}
   
	int j;	
	i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
        {
            cub->array[i * W_WIDTH + j] = cub->tab[i][j];
			//printf("array[%d] = %d \n", i * W_WIDTH + j , cub->array[i * W_WIDTH + j]);
            j++;
        }
        i++;
	}
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.window,cub->img, 0, 0);
}


/****Principle: rays are cast and tracedin groups based on some geometric
 *  constraints. For instance: on a 320×200 display resolution, a ray-caster
 *  traces only 320 rays (the number 320 comes from the fact that the display
 *  has 320 horizontal pixel resolution, hence 320 vertical column).*/
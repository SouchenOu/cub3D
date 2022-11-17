/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hori_vert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/17 10:21:44 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//3.14159265359 3.14159265359
//PIr 1.57079632679 // 3.14159265359 / 2
//PIl 4.71238898038 // 3 * 3.14159265359 / 2
//Depending on the looking angle of the player we can decide where the ray is actually hitting vertically (left or right) and horizontally (up or down

// now calculate the ray cordinate by using player cordinate and his looking angle
//horizontal // calculate the  ray is vector




/*******The basic idea of raycasting is as follows: the map is a 2D square grid, and each square can either be 0 (= no wall), 
 * or a positive value (= a wall with a certain color or texture).
For every x of the screen (i.e. for every vertical stripe of the screen), send out a ray that starts at the player
location and with a direction that depends on both the player's looking direction, and the x-coordinate of the screen.
Then, let this ray move forward on the 2D map, until it hits a map square that is a wall. If it hit a wall, calculate the distance
of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen: the further away
the wall, the smaller it's on screen, and the closer, the higher it appears to be. These are all 2D calculations. This image shows a 
	op down overview of two such rays (red) that start at the player (green dot) and hit blue walls:*/
void check_horizontal(t_ray *raycast)
{
	//int i ; 
	//i = 0;
	raycast->tang = -1/tan(raycast->ray_looking_angle);
	if (raycast->ray_looking_angle > 3.14159265359)                                                                             
	{
		raycast->ray_cordinate.y = ((raycast->cub->p.cord.y / size_GRID) * size_GRID) - (raycast->cub->dire.up);
		raycast->ray_cordinate.x = (raycast->cub->p.cord.y - raycast->ray_cordinate.y) * raycast->tang + raycast->cub->p.cord.x;
		raycast->number_to_check = raycast->cub->horizontal_num;  // nb lignes here 
		raycast->offset.y = -size_GRID;
		raycast->offset.x = -(raycast->offset.y) * raycast->tang;
		raycast->dir = UP;
		raycast->test = "horizontal";
	}
	if (raycast->ray_looking_angle < 3.14159265359 && raycast->ray_looking_angle != 0)
	{
		raycast->ray_cordinate.y = ((raycast->cub->p.cord.y / size_GRID) * size_GRID)  + (raycast->cub->dire.down);
		raycast->ray_cordinate.x = (raycast->cub->p.cord.y - raycast->ray_cordinate.y) * (raycast->tang) + raycast->cub->p.cord.x;
		raycast->number_to_check = raycast->cub->horizontal_num;
		raycast->offset.y = size_GRID;
		raycast->offset.x = -(raycast->offset.y) * raycast->tang;
		raycast->dir = DOWN;
		raycast->test = "horizontal";
	}
	
	else if (raycast->ray_looking_angle == 3.14159265359 || raycast->ray_looking_angle == 0)
	{
		raycast->ray_cordinate.x = raycast->cub->p.cord.x;
		raycast->ray_cordinate.y = raycast->cub->p.cord.y;
		raycast->number_to_check = -2;
		raycast->dir = LR;
	}
	//int i = 0;
	//x cordinate should not be sup than screen width && y cordinate should not be  sup than screen height
		//while (i < raycast->number_to_check && check_limits(raycast) == 1)
		//{
			//To calculate distance i should firstl check if the player look on a wall or not
			/******Each time the ray will hit a grid line horizontally or vertically, that point actually should be the position where we can check if it's a wall or not*/
/***To find the first wall that a ray encounters on its way, you have to let it start at the player's position,
 *  and then all the time, check whether or not the ray is inside a wall. If it's inside a wall (hit), 
 * then the loop can stop, calculate the distance, and draw the wall with the correct height. 
 * If the ray position is not in a wall, you have to trace it further: add a certain value to its position, 
 * in the direction of the direction of this ray, and for this new position, again check if it's inside a wall or not.
 *  Keep doing this until finally a wall is hit.*/
			/*if (is_it_wall(raycast, raycast->test))
			{
				if (!ft_strncmp(raycast->test, "horizontal", 10))
				{
					//printf("here orizontal");
					raycast->horizontal_cord.x = raycast->ray_cordinate.x;
					raycast->horizontal_cord.y = raycast->ray_cordinate.y;
					raycast->horizontal_distance = pyt(raycast->cub->p.cord.x, raycast->horizontal_cord.x, raycast->cub->p.cord.y, raycast->horizontal_cord.y);
				}
				break ;
			}
			else
			{
				//printf("add offeset\n");
				raycast->ray_cordinate.x = raycast->ray_cordinate.x + raycast->offset.x;
				raycast->ray_cordinate.y = raycast->ray_cordinate.y + raycast->offset.y;
			}
			i++;
		}
		if (!check_limits(raycast))
		{
			//printf("problem limits\n");
			
			if (!ft_strncmp(raycast->test, "horizontal", 10))
			{
				raycast->horizontal_cord.x = raycast->ray_cordinate.x;
				raycast->horizontal_cord.y = raycast->ray_cordinate.y;
				raycast->horizontal_distance= pyt(raycast->cub->p.cord.x, raycast->horizontal_cord.x, raycast->cub->p.cord.y, raycast->horizontal_cord.y);
			}
		}*/
}
void	check_vertical(t_ray *raycast)
{
	//int i = 0;
	//******************************************************************************/
	//vertical // get ray vector
	if (raycast->ray_looking_angle > 1.57079632679 && raycast->ray_looking_angle < 4.71238898038)
	{
		raycast->ray_cordinate.x = ((raycast->cub->p.cord.x / size_GRID) * size_GRID) - (raycast->cub->dire.left);
		raycast->ray_cordinate.y = ((raycast->cub->p.cord.x - raycast->ray_cordinate.x) * raycast->tang) + raycast->cub->p.cord.y;
		raycast->number_to_check = raycast->cub->virtical_num;
		raycast->offset.x = -size_GRID;
		raycast->offset.y = -(raycast->offset.x) * raycast->tang;
		raycast->dir = LEFT;
		raycast->test = "virtical";
	}
	else if (raycast->ray_looking_angle < 1.57079632679 || raycast->ray_looking_angle > 4.71238898038)
	{
		raycast->ray_cordinate.x = ((raycast->cub->p.cord.x / size_GRID) * size_GRID) + (raycast->cub->dire.right);
		raycast->ray_cordinate.y = (raycast->cub->p.cord.x - raycast->ray_cordinate.x) * raycast->tang + raycast->cub->p.cord.y;
		raycast->number_to_check = raycast->cub->virtical_num;
		raycast->offset.x = size_GRID;
		raycast->offset.y = -(raycast->offset.x) * raycast->tang;
		raycast->dir = RIGHT;
		raycast->test = "virtical";
	}
	else if (raycast->ray_looking_angle == 3.14159265359 || raycast->ray_looking_angle == 0)
	{
		raycast->ray_cordinate.x = raycast->cub->p.cord.x;
		raycast->ray_cordinate.y = raycast->cub->p.cord.y;
		raycast->number_to_check = -1;
		raycast->dir = UD;
	}
	/************************************************************************************************************************/
	//x cordinate should not be sup than screen width && y cordinate should not be  sup than screen height
	//int i = 0;
		//while (i < raycast->number_to_check && (raycast->ray_cordinate.x > 0 && raycast->ray_cordinate.y > 0) && (raycast->ray_cordinate.x < ((double)raycast->cub->virtical_num) * size_GRID) && (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size_GRID))
		//{
			//printf("yea\n");
			//To calculate distance i should firstl check if the player look on a wall or not
			/*if (is_it_wall(raycast, raycast->test))
			{
				if (!ft_strncmp(raycast->test, "virtical", 8))
				{
					raycast->virt_cord.x = raycast->ray_cordinate.x;
					raycast->virt_cord.y = raycast->ray_cordinate.y;
					raycast->virtical_distance = pyt(raycast->cub->p.cord.x, raycast->virt_cord.x, raycast->cub->p.cord.y, raycast->virt_cord.y);
				}
				break ;
			}
			else
			{
				raycast->ray_cordinate.x = raycast->ray_cordinate.x + raycast->offset.x;
				raycast->ray_cordinate.y = raycast->ray_cordinate.y + raycast->offset.y;
			}
			i++;
		}
		if (!check_limits(raycast))
		{
			if (!ft_strncmp(raycast->test, "virtical", 8))
				{
					raycast->virt_cord.x = raycast->ray_cordinate.x;
					raycast->virt_cord.y = raycast->ray_cordinate.y;
					raycast->virtical_distance = pyt(raycast->cub->p.cord.x, raycast->virt_cord.x, raycast->cub->p.cord.y, raycast->virt_cord.y);
				}
		}*/
	//*****************************************************************************/
	//printf("distance final = %f\n", raycast->final_distance);
}

int	check_limits(t_ray *raycast)
{
	if ((raycast->ray_cordinate.x > 0 && raycast->ray_cordinate.y > 0))
	{
		if (raycast->ray_cordinate.x < ((double)raycast->cub->virtical_num) * size_GRID)
		{
			if (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size_GRID)
				return (1);
		}
	}
	return (0);
}


//check if its a wall or not
int check_with_walls(t_wall *wall, t_cordinate cord, char *direction)
{
	int cmp = 0;
	int i = 0;
	t_wall	*temp;
	temp = wall;
	while (temp->next)
		{
				i = 0;
				cmp = 0;
			while (i < 4)
			{
				if (!ft_strncmp(direction, "horizontal", 10) && temp->wall_c[i].x == cord.x + size_GRID && temp->wall_c[i].y == cord.y + size_GRID)
				{
					cmp++;
				}
				else if (!ft_strncmp(direction, "virtical", 8) && temp->wall_c[i].x == cord.x && temp->wall_c[i].y == cord.y + size_GRID)
					cmp++;
				if (temp->wall_c[i].x == cord.x && temp->wall_c[i].y == cord.y)
					cmp++;
				if (cmp == 2)
					return (1);
				i++;
			}
			wall = temp->next;
		}
		return 0;
}
	

int	is_it_wall(t_ray *raycast, char *direction)
{	

	if (!ft_strncmp(direction, "virtical", 8))
	{
		raycast->ray_cord_temp.x = raycast->ray_cordinate.x;
		raycast->ray_cord_temp.y = find_x_or_y(raycast, direction);
		if(check_with_walls(raycast->cub->wall, raycast->ray_cord_temp, direction) == 1){
			return 1;
		}
	}
	if (!ft_strncmp(direction, "horizontal", 10))
	{
		raycast->ray_cord_temp.y = raycast->ray_cordinate.y;
		raycast->ray_cord_temp.x = find_x_or_y(raycast, direction);
		if(check_with_walls(raycast->cub->wall, raycast->ray_cord_temp, direction) == 1)
		{
			return 1;
		}
	}
	return (0);
}

double	find_x_or_y(t_ray *raycast, char *destination)
{
	double	i;
	double	nb;

	i = 0;
	if (!ft_strncmp(destination, "horizontal", 10))
	{
		nb = (double)raycast->cub->horizontal_num;
	}
	if (!ft_strncmp(destination, "vertical", 8))
		nb = (double)raycast->cub->virtical_num;
	while (i <= nb)
	{
		
		if (!ft_strncmp(destination, "vertical", 8))
		{
			if ((i * size_GRID) < raycast->ray_cordinate.y && ((i + 1) * size_GRID) > raycast->ray_cordinate.y)
				return (i * size_GRID);
		}
		else if (!ft_strncmp(destination, "horizontal", 10))
		{
			if ((i * size_GRID) < raycast->ray_cordinate.x && ((i + 1) * size_GRID) > raycast->ray_cordinate.x)
				return (i * size_GRID);
		}
		i++;
	}
	return (i * size_GRID);
}


void check_vertical_horizontal(t_ray *raycast)
{
	check_vertical(raycast);
	check_horizontal(raycast);
	
	if (raycast->virtical_distance < raycast->horizontal_distance)
		ray_cordinate(raycast, 'v');
	else if (raycast->virtical_distance > raycast->horizontal_distance)
		ray_cordinate(raycast, 'h');
	raycast->final_distance = pyt(raycast->cub->cord.x, raycast->ray_cordinate.x, raycast->cub->cord.y, raycast->ray_cordinate.y);
	printf("distance = %f\n", raycast->final_distance);
}


/**Field of view is the extent of the observable world that is seen at a given time either through someone's eyes,
 *  on a display screen, or through the viewfinder on a camera. Field of view (FOV) also describes the angle through which one can see that
 *  observable world*/

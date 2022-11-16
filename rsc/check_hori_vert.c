/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hori_vert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/16 17:12:33 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//3.14159265359 3.14159265359
//PIr 1.57079632679 // 3.14159265359 / 2
//PIl 4.71238898038 // 3 * 3.14159265359 / 2
//Depending on the looking angle of the player we can decide where the ray is actually hitting vertically (left or right) and horizontally (up or down

// now calculate the ray cordinate by using player cordinate and his looking angle
//horizontal // calculate the  ray is vector
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
	int i = 0;
	//x cordinate should not be sup than screen width && y cordinate should not be  sup than screen height
		while (i < raycast->number_to_check && check_limits(raycast) == 1)
		{
			//To calculate distance i should firstl check if the player look on a wall or not
			/******Each time the ray will hit a grid line horizontally or vertically, that point actually should be the position where we can check if it's a wall or not*/
			if (is_it_wall(raycast, raycast->test))
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
		}
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
	int i = 0;
		while (i < raycast->number_to_check && (raycast->ray_cordinate.x > 0 && raycast->ray_cordinate.y > 0) && (raycast->ray_cordinate.x < ((double)raycast->cub->virtical_num) * size_GRID) && (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size_GRID))
		{
			//printf("yea\n");
			//To calculate distance i should firstl check if the player look on a wall or not
			if (is_it_wall(raycast, raycast->test))
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
		}
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
int check_with_walls(t_wall *wall, t_cordinate *cord, char *direction)
{
	int cmp = 0;
	int i = 0;
	t_cordinate	*temp;
	temp = wall;
	while (temp->next)
		{
				i = 0;
				cmp = 0;
			while (i < 4)
			{
				if (!ft_strncmp(direction, "horizontal", 10) && temp->wall_c[i].x == cord->ray_cord_temp.x + size_GRID && temp->wall_c[i].y == cord->ray_cord_temp.y + size_GRID)
				{
					cmp++;
				}
				else if (!ft_strncmp(direction, "virtical", 8) && temp->wall_c[i].x == cord->ray_cord_temp.x && temp->wall_c[i].y == cord->ray_cord_temp.y + size_GRID)
					cmp++;
				if (temp->wall_c[i].x == cord->ray_cord_temp.x && temp->wall_c[i].y == cord->ray_cord_temp.y)
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
	printf("x = raycast->vert_cord.x= %f", raycast->ray_cordinate.x);
	printf("y = raycast->vert_cord.y = %f", raycast->ray_cordinate.y);
	check_horizontal(raycast);
	printf("x = raycast->horizontal_cord.x= %f", raycast->ray_cordinate.x);
	printf("y = raycast->horizontal_cord.y = %f", raycast->ray_cordinate.y);
	if (raycast->virtical_distance < raycast->horizontal_distance)
		ray_cordinate(raycast, 'v');
	else if (raycast->virtical_distance > raycast->horizontal_distance)
		ray_cordinate(raycast, 'h');
	raycast->final_distance = pyt(raycast->cub->cord.x, raycast->ray_cordinate.x, raycast->cub->cord.y, raycast->ray_cordinate.y);
	//printf("distance = %f\n", raycast->final_distance);
}


/**Field of view is the extent of the observable world that is seen at a given time either through someone's eyes,
 *  on a display screen, or through the viewfinder on a camera. Field of view (FOV) also describes the angle through which one can see that
 *  observable world*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hori_vert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 15:55:10 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//3.14159265359 3.14159265359
//PIr 1.57079632679 // 3.14159265359 / 2
//PIl 4.71238898038 // 3 * 3.14159265359 / 2
//Depending on the looking angle of the player we can decide where the ray is actually hitting vertically (left or right) and horizontally (up or down
void	check_horizontal_vertical(t_ray *raycast)
{
	int i ; 
	i = 0;
	raycast->tang = -tan(raycast->ray_looking_angle);
	//horizontal // get ray vector
	if (raycast->ray_looking_angle > 3.14159265359)                                                                             
	{
		raycast->ray_cordinate.y = ((raycast->cub->p.cord.y / size_GRID) * size_GRID) - (raycast->cub->dire.up);
		raycast->ray_cordinate.x = (raycast->cub->p.cord.y - raycast->ray_cordinate.y) * ((raycast->tang) + raycast->cub->p.cord.x);
		raycast->number_to_check = raycast->cub->horizontal_num;
		raycast->offset.y = -size_GRID;
		raycast->offset.x = -(raycast->offset.y) * raycast->tang;
		raycast->dir = UP;
		raycast->test = "horizontal";
	}
	if (raycast->ray_looking_angle < 3.14159265359 && raycast->ray_looking_angle != 0)
	{
		raycast->ray_cordinate.y = ((raycast->cub->p.cord.y / size_GRID) * size_GRID);
		printf("here= %f\n", raycast->ray_cordinate.y);
		raycast->ray_cordinate.x = (raycast->cub->p.cord.y - raycast->ray_cordinate.y) * ((raycast->tang) + raycast->cub->p.cord.x);
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
		raycast->number_to_check = -1;
		raycast->dir = LR;
	}

	/************************************************************************************************************************/
	//x cordinate should not be sup than screen width && y cordinate should not be  sup than screen height
		while (i < raycast->number_to_check && (raycast->ray_cordinate.x > 0 && raycast->ray_cordinate.y > 0) && (raycast->ray_cordinate.x < ((double)raycast->cub->virtical_num) * size_GRID) && (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size_GRID))
		{
			//To calculate distance i should firstl check if the player look on a wall or not
			if (is_it_wall(raycast, raycast->test))
			{
				if (!ft_strncmp(raycast->test, "virtical", 8))
				{
					raycast->virt_cord.x = raycast->ray_cordinate.x;
					raycast->virt_cord.y = raycast->ray_cordinate.y;
					raycast->virtical_distance = pyt(raycast->cub->p.cord.x, raycast->virt_cord.x, raycast->cub->p.cord.y, raycast->virt_cord.y);
				}
				else if (!ft_strncmp(raycast->test, "hozizontal", 10))
				{
					raycast->horizontal_cord.x = raycast->ray_cordinate.x;
					raycast->horizontal_cord.y = raycast->ray_cordinate.y;
					raycast->horizontal_distance = pyt(raycast->cub->p.cord.x, raycast->horizontal_cord.x, raycast->cub->p.cord.y, raycast->horizontal_cord.y);
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
				else if (!ft_strncmp(raycast->test, "hozizontal", 10))
				{
					raycast->horizontal_cord.x = raycast->ray_cordinate.x;
					raycast->horizontal_cord.y = raycast->ray_cordinate.y;
					raycast->horizontal_distance= pyt(raycast->cub->p.cord.x, raycast->horizontal_cord.x, raycast->cub->p.cord.y, raycast->horizontal_cord.y);
				}
		}
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
			printf("here6\n");
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
	 i = 0;
		while (i < raycast->number_to_check && (raycast->ray_cordinate.x > 0 && raycast->ray_cordinate.y > 0) && (raycast->ray_cordinate.x < ((double)raycast->cub->virtical_num) * size_GRID) && (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size_GRID))
		{
			//To calculate distance i should firstl check if the player look on a wall or not
			if (is_it_wall(raycast, raycast->test))
			{
				if (!ft_strncmp(raycast->test, "virtical", 8))
				{
					raycast->virt_cord.x = raycast->ray_cordinate.x;
					raycast->virt_cord.y = raycast->ray_cordinate.y;
					raycast->virtical_distance = pyt(raycast->cub->p.cord.x, raycast->virt_cord.x, raycast->cub->p.cord.y, raycast->virt_cord.y);
				}
				else if (!ft_strncmp(raycast->test, "hozizontal", 10))
				{
					raycast->horizontal_cord.x = raycast->ray_cordinate.x;
					raycast->horizontal_cord.y = raycast->ray_cordinate.y;
					raycast->horizontal_distance = pyt(raycast->cub->p.cord.x, raycast->horizontal_cord.x, raycast->cub->p.cord.y, raycast->horizontal_cord.y);
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
				else if (!ft_strncmp(raycast->test, "hozizontal", 10))
				{
					raycast->horizontal_cord.x = raycast->ray_cordinate.x;
					raycast->horizontal_cord.y = raycast->ray_cordinate.y;
					raycast->horizontal_distance= pyt(raycast->cub->p.cord.x, raycast->horizontal_cord.x, raycast->cub->p.cord.y, raycast->horizontal_cord.y);
				}
		}
	//******************************************************************************/
	if (raycast->virtical_distance < raycast->horizontal_distance)
		ray_cordinate(raycast, 'v');
	else if (raycast->virtical_distance > raycast->horizontal_distance)
		ray_cordinate(raycast, 'h');
	raycast->final_distance = pyt(raycast->cub->cord.x, raycast->ray_cordinate.x, raycast->cub->cord.y, raycast->ray_cordinate.y);
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


int	is_it_wall(t_ray *raycast, char *direction)
{
	int cmp;
	int i;
	if (!ft_strncmp(direction, "virtical", 8))
	{
		raycast->ray_cord_temp.x = raycast->ray_cordinate.x;
		raycast->ray_cord_temp.y = find_x_or_y(raycast, direction);
		while (raycast->cub->wall->next)
		{
				i = 0;
				cmp = 0;
			while (i < 4)
			{
				if (!ft_strncmp(direction, "horizontal", 10) && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x + size_GRID && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y + size_GRID)
					cmp++;
				else if (!ft_strncmp(direction, "virtical", 8) && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y + size_GRID)
					cmp++;
				if (raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y)
					cmp++;
				if (cmp == 2)
					return (1);
				i++;
			}
			raycast->cub->wall = raycast->cub->wall->next;
		}
	}
	else if (!ft_strncmp(direction, "horizontal", 10))
	{
		raycast->ray_cord_temp.y = raycast->ray_cordinate.y;
		raycast->ray_cord_temp.x = find_x_or_y(raycast, direction);
		while (raycast->cub->wall->next)
		{
			i = 0;
				cmp = 0;
			while (i < 4)
			{
				if (!ft_strncmp(direction, "horizontal", 10) && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x + size_GRID && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y)
					cmp++;
				else if (!ft_strncmp(direction, "vertical", 8) && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y + size_GRID)
					cmp++;
				if (raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y)
					cmp++;
				if (cmp == 2)
					return (1);
				i++;
			}
			raycast->cub->wall = raycast->cub->wall->next;
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
		nb = (double)raycast->cub->horizontal_num;
	if (!ft_strncmp(destination, "vertical", 8))
		nb = (double)raycast->cub->virtical_num;
	while (i <= nb)
	{
		if (!ft_strncmp(destination, "vertical", 8))
		{
			if ((i * size_GRID) < raycast->ray_cordinate.y && ((i + 1) * size_GRID) > raycast->ray_cordinate.y)
				return (i * size_GRID);
		}
		else if (ft_strncmp(destination, "horizontal", 10))
		{
			if ((i * size_GRID) < raycast->ray_cordinate.x && ((i + 1) * size_GRID) > raycast->ray_cordinate.x)
				return (i * size_GRID);
		}
		i++;
	}
	return (i * size_GRID);
}





/**Field of view is the extent of the observable world that is seen at a given time either through someone's eyes,
 *  on a display screen, or through the viewfinder on a camera. Field of view (FOV) also describes the angle through which one can see that
 *  observable world*/

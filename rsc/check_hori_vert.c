/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/12 20:48:17 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//3.14159265359 3.14159265359
//PIr 1.57079632679 // 3.14159265359 / 2
//PIl 4.71238898038 // 3 * 3.14159265359 / 2
void	check_horizontal_vertical(t_ray *raycast)
{
	//horizontal // get ray vector
	if (raycast->ray_looking_angle > 3.14159265359)                                                                             
	{
		raycast->ray_cordinate.y = ((raycast->cub->cord.y / size_GRID) * size_GRID) - (raycast->cub->dire.up);
		raycast->ray_cordinate.x = (raycast->cub->cord.y - raycast->ray_cordinate.y) / ((-tan(raycast->ray_looking_angle)) + raycast->cub->cord.x);
		raycast->number_to_check = raycast->cub->horizontal_num;
		raycast->offset.y = -size_GRID;
		raycast->offset.x = -(raycast->offset.y) * raycast->tang;
		raycast->dir = UP;
	}
	else if (raycast->ray_looking_angle < 3.14159265359)
	{
		raycast->ray_cordinate.y = ((raycast->cub->cord.y / size_GRID) * size_GRID) + (raycast->cub->dire.down);
		raycast->ray_cordinate.x = (raycast->cub->cord.y - raycast->ray_cordinate.y) / ((-tan(raycast->ray_looking_angle)) + raycast->cub->cord.x);
		raycast->number_to_check = raycast->cub->horizontal_num;
		raycast->offset.y = size_GRID;
		raycast->offset.x = -(raycast->offset.y) * raycast->tang;
		raycast->dir = DOWN;
		raycast->test = 'h';
	}
	else if (raycast->ray_looking_angle == 3.14159265359 || raycast->ray_looking_angle == 0)
	{
		raycast->ray_cordinate.x = raycast->cub->cord.x;
		raycast->ray_cordinate.y = raycast->cub->cord.y;
		raycast->number_to_check = -1;
		raycast->dir = LR;
		raycast->test = 'h';
	}
	//vertical // get ray vector
	raycast->tang = -tan(raycast->ray_looking_angle);
	if (raycast->ray_looking_angle > 1.57079632679 && raycast->ray_looking_angle < 4.71238898038)
	{
		raycast->ray_cordinate.x = ((raycast->cub->cord.x / size_GRID) * size_GRID) - (raycast->cub->dire.left);
		raycast->ray_cordinate.y = ((raycast->cub->cord.x - raycast->ray_cordinate.x) * raycast->tang) + raycast->cub->cord.y;
		raycast->number_to_check = raycast->cub->virtical_num;
		raycast->offset.x = -size_GRID;
		raycast->offset.y = -(raycast->offset.x) * raycast->tang;
		raycast->dir = LEFT;
		raycast->test = 'v';
	}
	else if (raycast->ray_looking_angle < 1.57079632679 || raycast->ray_looking_angle > 4.71238898038)
	{
		raycast->ray_cordinate.x = ((raycast->cub->cord.x / size_GRID) * size_GRID) + (raycast->cub->dire.right);
		raycast->ray_cordinate.y = (raycast->cub->cord.x - raycast->ray_cordinate.x) * raycast->tang + raycast->cub->cord.y;
		raycast->number_to_check = raycast->cub->virtical_num;
		raycast->offset.x = size_GRID;
		raycast->offset.y = -(raycast->offset.x) * raycast->tang;
		raycast->dir = RIGHT;
		raycast->test = 'v';
	}
	else if (raycast->ray_looking_angle == 3.14159265359 || raycast->ray_looking_angle == 0)
	{
		raycast->ray_cordinate.x = raycast->cub->cord.x;
		raycast->ray_cordinate.y = raycast->cub->cord.y;
		raycast->number_to_check = -1;
		raycast->dir = UD;
	}
	if(raycast->test == 'h')
	{
		check_if_wall_and_cal_dis(raycast, 'h');

	}else if (raycast->test == 'v')
	{
		check_if_wall_and_cal_dis(raycast, 'v');
	}
	if (raycast->virtical_distance < raycast->horizontal_distance)
		ray_cordinate(raycast, 'v');
	else if (raycast->virtical_distance > raycast->horizontal_distance)
		ray_cordinate(raycast, 'h');
	raycast->final_distance = pyt(raycast->cub->cord.x, raycast->ray_cordinate.x, raycast->cub->cord.y, raycast->ray_cordinate.y);
}

int	check_limits(t_ray *raycast)
{
	if ((raycast->ray_cordinate.x > 0&& raycast->ray_cordinate.y > 0))
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


int	is_wall(t_ray *raycast, int direction)
{
	if (direction == 'v')
	{
		raycast->ray_cord_temp.x = raycast->ray_cordinate.x;
		raycast->ray_cord_temp.y = find_x_or_y(raycast, direction);
		while (raycast->cub->wall->next)
		{
				i = 0;
				cmp = 0;
			while (i < 4)
			{
				if (direction == 'h' && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x + size_GRID && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y)
					cmp++;
				else if (direction == 'v' && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y + size_GRID)
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
	else if (direction == 'h')
	{
		raycast->ray_cord_temp.y = raycast->ray_cordinate.y;
		raycast->ray_cord_temp.x = find_x_or_y(raycast, direction);
		while (raycast->cub->wall->next)
		{
			i = 0;
				cmp = 0;
			while (i < 4)
			{
				if (direction == 'h' && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x + size_GRID && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y)
					cmp++;
				else if (direction == 'v' && raycast->cub->wall->wall_c[i].x == raycast->ray_cord_temp.x && raycast->cub->wall->wall_c[i].y == raycast->ray_cord_temp.y + size_GRID)
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

double	find_x_or_y(t_ray *raycast, int destination)
{
	double	i;
	double	nb;

	i = 0;
	if (destination == 'v')
		nb = (double)raycast->cub->horizontal_num;
	if (destination == 'h')
		nb = (double)raycast->cub->virtical_num;
	while (i <= nb)
	{
		if (destination == 'v')
		{
			if ((i * size_GRID) < raycast->ray_cordinate.y && ((i + 1) * size_GRID) > raycast->ray_cordinate.y)
				return (i * size_GRID);
		}
		else if (destination == 'h')
		{
			if ((i * size_GRID) < raycast->ray_cordinate.x && ((i + 1) * size_GRID) > raycast->ray_cordinate.x)
				return (i * size_GRID);
		}
		i++;
	}
	return (i * size_GRID);
}

void	check_if_wall_and_cal_dis(t_ray *raycast, int direction)
{
	int	i;

	i = 0;
	while (i < raycast->number_to_check && (raycast->ray_cordinate.x > 0 && raycast->ray_cordinate.y > 0) && (raycast->ray_cordinate.x < ((double)raycast->cub->virtical_num) * size_GRID) && (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size_GRID))
	{
		if (is_wall(raycast, direction))
		{
			if (direction == 'v')
			{
				raycast->virt_cord.x = raycast->ray_cordinate.x;
				raycast->virt_cord.y = raycast->ray_cordinate.y;
				raycast->virtical_distance = pyt(raycast->cub->cord.x, raycast->virt_cord.x, raycast->cub->cord.y, raycast->virt_cord.y);
			}
			else if (direction == 'h')
			{
				raycast->horizontal_cord.x = raycast->ray_cordinate.x;
				raycast->horizontal_cord.y = raycast->ray_cordinate.y;
				raycast->horizontal_distance = pyt(raycast->cub->cord.x, raycast->horizontal_cord.x, raycast->cub->cord.y, raycast->horizontal_cord.y);
			}
			break ;
		}
		else
		{
			raycast->ray_cordinate.x += raycast->offset.x;
			raycast->ray_cordinate.y += raycast->offset.y;
		}
		i++;
	}
	if (!check_limits(raycast))
	{
		if (direction == 'v')
			{
				raycast->virt_cord.x = raycast->ray_cordinate.x;
				raycast->virt_cord.y = raycast->ray_cordinate.y;
				raycast->virtical_distance = pyt(raycast->cub->cord.x, raycast->virt_cord.x, raycast->cub->cord.y, raycast->virt_cord.y);
			}
			else if (direction == 'h')
			{
				raycast->horizontal_cord.x = raycast->ray_cordinate.x;
				raycast->horizontal_cord.y = raycast->ray_cordinate.y;
				raycast->horizontal_distance= pyt(raycast->cub->cord.x, raycast->horizontal_cord.x, raycast->cub->cord.y, raycast->horizontal_cord.y);
			}
	}
}


/**Field of view is the extent of the observable world that is seen at a given time either through someone's eyes,
 *  on a display screen, or through the viewfinder on a camera. Field of view (FOV) also describes the angle through which one can see that
 *  observable world*/

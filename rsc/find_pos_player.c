/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pos_player.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/12 13:11:44 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"





/* I do that to check if the player position was between
gridlines or on one the gridLine so we can have the right distance for
gridline hitting */


//Player position (virtical or horizontal)
void find_pos_player(t_struct *cub){

    double	i;
    double  j;
	cub->mlx.height = 0;
	cub->mlx.width = 0;
    cub->cord.x = 100.00;
	cub->cord.y = 220.00;
    cub->vect.x = cos(degrees_to_radians(280.00));
	cub->vect.y = -sin(degrees_to_radians(280.00));
	cub->vect.pos = 280.00;
    cub->dire.down = 0;
	cub->dire.up = 0;
	cub->dire.left = 0;
	cub->dire.right = 0;
    cub->virtical_num = cub->map_width;// nb characters
    cub->horizontal_num= cub->map_height; //nb lignes

	i = 0;
    j = 0;
	while (i <= (double)cub->horizontal_num)
	{
		if (cub->cord.y < ((i + 1) * size_GRID) && cub->cord.y > (i * size_GRID))
		{
			cub->dire.up = cub->cord.y - (i * size_GRID);
			cub->dire.down = ((i + 1) * size_GRID) - cub->cord.y;

		}
        i++;
	}

	while (j <= (double)cub->virtical_num)
	{
		if ((j * size_GRID) < cub->cord.x && ((j + 1) * size_GRID) > cub->cord.x)
		{
			cub->dire.left = cub->cord.x - (j * size_GRID);
			cub->dire.right = ((j + 1) * size_GRID) - cub->cord.x;
		}
		j++;
	}
}



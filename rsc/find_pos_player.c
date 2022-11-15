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

	i = 0;
    j = 0;
	while (i <= (double)cub->horizontal_num)
	{
		if (cub->p.cord.y < ((i + 1) * size_GRID) && cub->p.cord.y > (i * size_GRID))
		{
			cub->dire.up = cub->p.cord.y - (i * size_GRID);
			cub->dire.down = ((i + 1) * size_GRID) - cub->p.cord.y;
			printf("here1 = %f\n", cub->dire.up);
			printf("here2 = %f\n", cub->dire.down);

		}
        i++;
	}

	while (j <= (double)cub->virtical_num)
	{
		if ((j * size_GRID) < cub->p.cord.x && ((j + 1) * size_GRID) > cub->p.cord.x)
		{
			cub->dire.left = cub->p.cord.x - (j * size_GRID);
			cub->dire.right = ((j + 1) * size_GRID) - cub->p.cord.x;
			printf("here1 = %f\n", cub->dire.right);
			printf("here2 = %f\n", cub->dire.left);

		}
		j++;
	}
}



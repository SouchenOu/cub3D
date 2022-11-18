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

// if the player is between gredline we do  sostraction to get lq distqnce qui on a doit sostracter after when we calculate ray cordinate 
//Player position (virtical or horizontal)
void find_pos_player(t_struct *cub)
{

    double	i;
    double  j;

	i = 0;
    j = 0;

	while (i <= (double)cub->horizontal_num)
	{
		if (cub->player.position_y < ((i + 1) * size_GRID) && cub->player.position_y > (i * size_GRID))
		{
		
			cub->dire.up = cub->player.position_y - (i * size_GRID);
			cub->dire.down = ((i + 1) * size_GRID) - cub->player.position_y;
		
		

		}
        i++;
	}

	while (j <= (double)cub->virtical_num)
	{
		if ((j * size_GRID) < cub->player.position_x && ((j + 1) * size_GRID) > cub->player.position_x)
		{
			cub->dire.left = cub->player.position_x - (j * size_GRID);
			cub->dire.right = ((j + 1) * size_GRID) - cub->player.position_x;
	

		}
		j++;
	}
}



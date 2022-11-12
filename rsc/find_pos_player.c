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





/* >>>> horizontal <<<< *
find where is the pos of the player btwn the horizontal 
lines or on the one of the gridlines
?       (y - 1) < posY && (y + 1) > posY

----- UP
if player was looking up then
? h_initial = posY - (y - 1);
rayY - h_initial;

----- DOWN
if player was looking down then
? h_initial = (y + 1) - posY;
rayY + h_initial;

* >>>> vertical <<<< *
find where is the pos of the player btwn the vertical 
lines or on the one of the gridlines
?       (x - 1) < posX && (x + 1) > posX

----- RIGHT
if player is looking right then 
? v_initial = (x + 1) - posX;
rayX + v_initial;

----- LEFT
if player is looking left then
? v_initial = posX - (x - 1);
rayX - v_initial;

*/


//Player position (virtical or horizontal)
void find_pos_player(t_struct *cub){

    double	i;
    double  j;
	cub->mlx_info.height = 0;
	cub->mlx_info.width = 0;
    cub->cord.x = 100.00;
	cub->cord.y = 220.00;
    cub->vect.x = cos(degrees_to_radians(280.00));
	cub->vect.y = -sin(degrees_to_radians(280.00));
	cub->vect.pos = 280.00;
    cub->dire.down = 0.00;
	cub->dire.up = 0.00;
	cub->dire.left = 0.00;
	cub->dire.right = 0.00;
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



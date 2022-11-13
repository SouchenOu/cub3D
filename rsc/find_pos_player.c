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
    cub->cord.x = 200.0;
	cub->cord.y = 100.0;
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
	printf("x-player = %f\n", cub->playerP.x);
	printf("y player = %f\n", cub->playerP.y);
	while (i <= (double)cub->horizontal_num)// here i put the number of lignes
	{
     // here cub->cord.y && cub->cord.x is the cordinate of my player
	 // i shoose player position so, I put it x = 200 and y = 100
	 // cordinate player in this map x = 8 and y = 24

		if (cub->playerP.y < ((i + 1) * size_GRID) && cub->playerP.y > (i * size_GRID))
		{
			cub->dire.up = cub->playerP.y - (i * size_GRID);
			cub->dire.down = ((i + 1) * size_GRID) - cub->playerP.y;
			printf("up here = %f\n", cub->dire.up);
			printf("down here = %f\n", cub->dire.down);

		}
        i++;
	}

	while (j <= (double)cub->virtical_num)
	{
		if ((j * size_GRID) < cub->playerP.x && ((j + 1) * size_GRID) > cub->playerP.x)
		{
			cub->dire.left = cub->playerP.x - (j * size_GRID);
			cub->dire.right = ((j + 1) * size_GRID) - cub->playerP.x;
			printf("left here = %f\n", cub->dire.left);
			printf("right here = %f\n", cub->dire.right);
		}
		j++;
	}
}



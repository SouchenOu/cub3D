/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/14 00:14:08 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void player_position(t_struct *cub){
    int i = 0;
    int j = 0;
   char** data = ft_jump_lines(cub);
   int  height = ft_count_height(data);
   
    cub->scaleHeight = W_HEIGHT/ height;
    cub->scaleWidth = W_WIDTH/ cub->width;
   while (data[i])
   {
        j = 0;
        while(data[i][j])
        {
            if (data[i][j] == 'E'|| data[i][j] == 'N' || data[i][j] == 'S' || data[i][j] == 'W')
            {
                cub->player.position_x = j * cub->scaleWidth;
                cub->player.position_y = i * cub->scaleHeight;
                return ;
            }
            j++;
        }
        i++;
   } 
}



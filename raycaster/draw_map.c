/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/18 23:20:09 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_struct *ptr, int x, int y, long color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		dst = ptr->arrayColor + (y * ptr->line_length + x
				* (ptr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
int ft_count_height(char **data)
{
    int len;
    int i;
    int j;

    i = 0;
    len = 0;
    while (data[i])
    {
        j = 0;
        while (data[i][j])
        {
          if (j == 0)
            len++;
          j++;  
        }
      i++;  
    }
   return (len); 
}

void    ft_draw_map(t_struct *cub)
{
    int x;
    int y;
    char    **data;
    int     len;

    y = 0;
    len = 0;
    data = ft_jump_lines(cub);
    //cub->fovAngle = 60 * (M_PI / 180);
    cub->NB_rays = W_WIDTH;
    // cub->rayAngle = cub->player.rottAngle;
    while (data[y])
    {
        x = 0;
        while (data[y][x])
        {
            if (data[y][x] == '1')
                draw_cub(cub, x, y, 0xFFF0000);
            else if (data[y][x] == '0')
                draw_cub(cub, x, y, 0);
            x++;
        }
        y++;
    }
    drawRaysOfplyer(cub, cub->player.position_x, cub->player.position_y , 0xFFFF0F);   
    draw_player(cub, cub->player.position_x, cub->player.position_y , 0xfffff);
    mlx_put_image_to_window(cub->mlx.mlx_ptr , cub->mlx.window, cub->img, 0, 0);
}

void    draw_cub(t_struct *ptr, int x, int y, int color)
{
    int start_x;
    int start_y;
    int     i;
    int     j;

        
        start_x = x * ptr->scaleWidth;
        start_y = y * ptr->scaleHeight;
        i = start_y;
        j = start_x;
        while (i < start_y + ptr->scaleHeight)
        {
        j =  start_x;
        while (j < start_x + ptr->scaleWidth)
        {
            my_mlx_pixel_put(ptr, j, i, color);
            j++;
         }
        i++;
    }
}


void directionOfPlayer(t_struct *cub)
{
    char** data = ft_jump_lines(cub);
    int gred_y = floor(cub->player.position_y/cub->scaleHeight);
    int gred_x = floor(cub->player.position_x/cub->scaleWidth);
    if (data[gred_y][gred_x] == 'N')
        cub->player.rottAngle = M_PI / 2;
    if (data[gred_y][gred_x] == 'S')
        cub->player.rottAngle = M_PI * (3/ 2);
    if (data[gred_y][gred_x] == 'W')
        cub->player.rottAngle = M_PI;
    if (data[gred_y][gred_x] == 'E')
        cub->player.rottAngle = 0;
}

void player_position(t_struct *cub){
    int i = 0;
    int j = 0;
   char** data = ft_jump_lines(cub);
   int  height = ft_count_height(data);
   
    cub->scaleHeight = W_HEIGHT/ height;
    cub->scaleWidth = W_WIDTH/ cub->width;
    cub->player.rottSpeed = 0.174533;
    cub->player.walkDrctn = 0;
   
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

int	player_move(int key, t_struct *p)
{
	if (key == 125)
		p->player.position_y += 1;
	if (key == 126)
		p->player.position_y -= 1;
	if (key == 124)
		p->player.position_x += 1;
	if (key == 123)
		p->player.position_x -= 1;
    mlx_destroy_image(p->mlx_ptr, p->img);
    p->img = mlx_new_image(p->mlx_ptr, W_WIDTH, W_HEIGHT);
    update_ptayer(p);
    return (0);
}
void update_ptayer(t_struct *cub){
    int     x;
    int     y;
    char    **data;
    int     len;

    y = 0;
    len = 0;
    data = ft_jump_lines(cub);
    while (data[y])
    {
        x = 0;
        while (data[y][x])
        {
            if (data[y][x] == '1')
                draw_cub(cub, x, y, 0xFF00000);
            else if (y == cub->player.position_y && x == cub->player.position_x){
                draw_cub(cub, x, y, 0xfffff);
            }
            else
                draw_cub(cub, x, y, 0);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 1, 1);
}
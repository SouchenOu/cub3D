/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/14 00:14:32 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_struct *ptr, int x, int y, long color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		dst = ptr->addr + (y * ptr->line_length + x
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

int castRays(t_struct *cub)
{
    int i;
    i = 0;
    while (i < cub->numOfRays)
    {
       cub->rays[i] = cub->rayAngle;
       cub->rayAngle += cub->fovAngle / cub->numOfRays;
        //  printf("hey %f\n",cub->rays[i]);
       i++;
    }
    return (0);
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
    cub->fovAngle = 60 * (M_PI / 180);
    cub->numOfRays = W_WIDTH / 4;
    cub->rayAngle = cub->player.rottAngle - (cub->fovAngle + 0.5);
    castRays(cub);
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
    // else if ((y  == cub->player.position_y / cub->scaleHeight) && (x == cub->player.position_x / cub->scaleWidth)){
    //  drawRaysOfplyer(cub, cub->player.position_x, cub->player.position_y , 0xFFFF0F);   
        draw_player(cub, cub->player.position_x, cub->player.position_y , 0xfffff); 
    // }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}


int	player_move(int key, t_struct *cub)
{ 
    int gred_x = cub->player.position_x;
    int gred_y = cub->player.position_y;
	if (key == 1){
		 gred_y += 3;
    }
	else if (key == 13)
    {
		 gred_y -= 3;
    }
	else if (key == 2){
		 gred_x += 3;
    }
	else if (key == 0){
		 gred_x -= 3;
    }
    else if (key == 124)
    {
		cub->player.rottAngle += M_PI / 6;
    }
	else if (key == 123){
		cub->player.rottAngle -= M_PI / 6;
    }
    else {return (0);}
    if (check_wall(cub, gred_x, gred_y) != 1)
    {
        float new_x = gred_x + (cos(cub->player.rottAngle) * cub->scaleWidth);
    float new_y = gred_y + (sin(cub->player.rottAngle) * cub->scaleHeight);
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }
    mlx_destroy_image(cub->mlx_ptr, cub->img);
    cub->img = mlx_new_image(cub->mlx_ptr, W_WIDTH, W_HEIGHT);
    ft_draw_map(cub);
    return (0);
}

void directionOfPlayer(t_struct *cub){
    
    char** data = ft_jump_lines(cub);
    if (data[cub->player.position_y/cub->scaleHeight][cub->player.position_x/cub->scaleWidth] == 'N')
        cub->player.rottAngle = M_PI * 3 / 2;
    if (data[cub->player.position_y/cub->scaleHeight][cub->player.position_x/cub->scaleWidth] == 'S')
        cub->player.rottAngle = M_PI / 2;
    if (data[cub->player.position_y/cub->scaleHeight][cub->player.position_x/cub->scaleWidth] == 'W')
        cub->player.rottAngle = M_PI;
    if (data[cub->player.position_y/cub->scaleHeight][cub->player.position_x/cub->scaleWidth] == 'E')
        cub->player.rottAngle = 0;
}

void draw_player(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;
    // printf("x-->%d\n", x);
    // printf("y-->%d\n", y);
   	// // float new_x = x + cos(cub->player.rottAngle) * 3;
    // // float new_y = y + sin(cub->player.rottAngle) * 3;
    
    // printf("new_x-->%f\n", new_x);
    //   printf("new_y-->%f\n", new_y);
	x_1 = x + cos(cub->player.rottAngle) * 42;
    y_1 = y + sin(cub->player.rottAngle) * 42;
    ddaForLine(cub, x, y, x_1, y_1, color);  
}

void drawRaysOfplyer(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;
    int i = 0;
   // printf("x-->%d\n", x);
      //  printf("hey %d\n", cub->rays[i]);
      castRays(cub);
   while (cub->rays[i])
   {
        x_1 = x + cos(cub->rays[i]) * 100;
        y_1 = y + sin(cub->rays[i]) * 100;
    // printf("x_1-->%d\n", x_1);
        ddaForLine(cub, x, y, x_1, y_1, color);  
        i++;
   }
   
}

// Function for finding absolute value
int abs(int n) 
{ 
    if (n > 0){
        return (n);
    }
    else {
        return (n *(-1));
    }
}
// DDA Function for line generation
void ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color)
{
    // calculate dstnc_x & dstnc_y
    int dstnc_x = x_1 - x_0;
    int dstnc_y = y_1 - y_0;
 
    // calculate steps required for generating pixels
    int steps;
    if (abs(dstnc_x) > abs(dstnc_y))
        steps = abs(dstnc_x);
    else
        steps = abs(dstnc_y);
    // calculate increment in x & y for each steps
    float x_inc = dstnc_x / (float)steps;
    float y_inc = dstnc_y / (float)steps;
    // Put pixel for each step
    float x = x_0;
    float y = y_0;
    int i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += x_inc; // increment in x at each step
       y += y_inc; // increment in y at each step
       i++;
    }
}
 
 int check_wall(t_struct *cub, int gred_x, int gred_y)
 {
    char **map;

    map = ft_jump_lines(cub);
   /// printf("---> %cC\n",map[gred_y/cub->scaleHeight][gred_x/cub->scaleWidth]);
    if (map[gred_y/cub->scaleHeight][gred_x/cub->scaleWidth] == '1')
        return (1);
    return (0);
 }
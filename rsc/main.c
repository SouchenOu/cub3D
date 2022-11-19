/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/19 03:34:32 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print(char **str)
{
     int i = 0;
    while (str[i])
    {
        printf("|%s|\n",str[i]);
        i++;
    }
}
void ft_colorBuffer(t_struct *cub)
{
    int i;
    int k;
    i = 0;
	while (i < W_HEIGHT)
	{
		k = 0;
		while (k < W_WIDTH)
        {
            cub->colorBuffer[i][k] = 0;
            k++;
        }
        i++;
	}
    cub->check = 0;
}

void initial(t_struct *cub)
{
    cub->mlx.height = 0;
	cub->mlx.width = 0;
    //cub->p.cord.x = 100.00;
	//cub->p.cord.y = 220.00;
    cub->p.vect.x = cos(degrees_to_radians(cub->player.rottAngle));
	cub->p.vect.y = -sin(degrees_to_radians(cub->player.rottAngle));
	//cub->p.vect.pos = 280.00;
    cub->dire.down = 0.00;
	cub->dire.up = 0.00;
	cub->dire.left = 0.00;
	cub->dire.right = 0.00;
    cub->virtical_num = cub->width;// nb characters
    cub->horizontal_num= cub->height; //nb lignes
	cub->FOV = 60.00;
	cub->NB_rays = W_WIDTH;
	cub->looking_angle = cub->player.rottAngle - ((double)cub->FOV / 2.00);
	

    /*we define the FOV to be 60 degrees through 
	trial and experimentation (on how good it looks
	 on screen)*/
	//cub->FOV = 60;
	//Dimension of the Projection Plane = W_WIDTH
	//cub->NB_rays =  W_WIDTH;
	//cub->looking_angle = 280 - ((double)cub->FOV / 2);
	//cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);
}

void	ft_ray(t_struct *cub)
{
	int	i;
	int x;
	int y;
	char **data;
	y = 0;
	x = 0;

	data = ft_jump_lines(cub);
	//printf("first lokking angle = %d\n", cub->looking_angle);
	cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);
	i = 0;
	while (i < cub->NB_rays)
	{
		initial_every_ray(cub, &cub->raycast[i], cub->looking_angle);
		cub->looking_angle = cub->looking_angle + (cub->FOV / (double)cub->NB_rays);

        i++;
	}
	/*while (data[y])
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
    }*/
}

void initial_every_ray(t_struct *cub, t_ray *raycast, double looking_angle)
{
		raycast->cub = cub;
		raycast->ray_looking_angle = degrees_to_radians(limite_angle(looking_angle));
		//printf("lo_angle=%f\n", looking_angle);
		//printf("ray_looking = %f\n", raycast->ray_looking_angle );
		raycast->ray_cordinate.x = -1.00;
		raycast->ray_cordinate.y = -1.00;
		raycast->offset.x = -1.00;
		raycast->offset.y = -1.00;
		raycast->dir = 0.00;
		raycast->number_to_check = -2;
		raycast->tang = 0;
		//cub.p.cord.y = 220.00;
    	//cub.p.vect.x = cos(degrees_to_radians(280.00));
		//cub.p.vect.y = -sin(degrees_to_radians(280.00));
		raycast->horizontal_distance = 0.00;
		raycast->horizontal_cord.y = 0.00;
		raycast->horizontal_cord.x = 0.00;
		raycast->virt_cord.x = 0.00;
		raycast->virt_cord.y = 0.00;
		raycast->virtical_distance = 0.00;
        raycast->ray_cord_temp.x = 0.00;
        raycast->ray_cord_temp.y = 0.00;
		raycast->dest = 0.00;
		raycast->wallStripHeight = 0.00;
		raycast->final_distance = 0.00;

		

}
void check_nextSteep(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->player.position_x + (cos(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 4));
    new_y = cub->player.position_y + (sin(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 4));
    if (check_wall(cub, new_x, new_y) != 1)
    {
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }   
}

void check_downSteep(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->player.position_x + (cos(cub->player.rottAngle + (M_PI/2)) * ((double)cub->player.walkDown * 4));
    new_y = cub->player.position_y + (sin(cub->player.rottAngle + (M_PI/2)) * ((double)cub->player.walkDown * 4));
    if (check_wall(cub, new_x, new_y) != 1)
    {
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }   
}
 int check_wall(t_struct *cub, double x, double y)
 {
    char **map;
    map = ft_jump_lines(cub);
    int gred_y = (int)(y/cub->scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = (int)(x/cub->scaleWidth);
    if (!map[gred_y])
        return (1);
    if ( map[gred_y][gred_x] == '1' ||  !map[gred_y])
        return (1);
    return (0);
 }
int	player_move(int key, t_struct *cub)
{ 
    cub->player.walkDrctn = 0;
	if (key == 1){
        cub->player.walkDrctn = -1;
		check_nextSteep(cub);
    }
	else if (key == 13){
        cub->player.walkDrctn = 1;
       check_nextSteep(cub);
    }
	else if (key == 2){
        cub->player.walkDown = 1;
		check_downSteep(cub);
    }
	else if (key == 0){
        cub->player.walkDown= -1;
		check_downSteep(cub);
    }
    else if (key == 124)
        cub->player.rottAngle += cub->player.rottSpeed;
	else if (key == 123)
        cub->player.rottAngle -= cub->player.rottSpeed;
    mlx_destroy_image(cub->mlx.mlx_ptr , cub->img);
    cub->img = mlx_new_image(cub->mlx.mlx_ptr , W_WIDTH, W_HEIGHT);
    ft_draw_map(cub);
    return (0);
}
int main(int ac, char **av)
{
    int i;
    i = 0;
    t_struct cub;
	//t_ray raycast;
    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
    
	if (ft_read_maps(av[1], &cub) == 0)
        return (0);
	if (!ft_check_alltextures(&cub))
        return (0); 
	if (!ft_check_rgb(&cub))
        return (0);
	if (!ft_check_map(&cub))
        return (0);

    cub.mlx.mlx_ptr = mlx_init();
	cub.mlx.window = mlx_new_window(cub.mlx.mlx_ptr, W_WIDTH, W_HEIGHT, "Souchen_ysmaili'Cub3d");
	cub.img = mlx_new_image(cub.mlx.mlx_ptr, W_WIDTH,  W_HEIGHT);
	cub.arrayColor = mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
	player_position(&cub);
	find_pos_player(&cub);
    directionOfPlayer(&cub);
	initial(&cub);//normilay find and ft_ray
	ft_ray(&cub);
    ft_draw_map(&cub);

    
	
    //printf("cord = %f\n",cub.p.cord.x );
    //raycast(&cub);
	                                                                                   
    mlx_key_hook(cub.mlx.window, &move, &cub);
	//mlx_key_hook(cub.mlx.window, &move, &player_move);
	//mlx_hook(cub.mlx.window, 17, 1L << 17, &endgame, &cub);
    mlx_loop(cub.mlx.mlx_ptr);
   
}
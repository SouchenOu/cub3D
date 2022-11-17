/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/17 15:22:41 by souchen          ###   ########.fr       */
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
    cub->p.cord.x = 100.00;
	cub->p.cord.y = 220.00;
    cub->p.vect.x = cos(degrees_to_radians(280.00));
	cub->p.vect.y = -sin(degrees_to_radians(280.00));
	cub->p.vect.pos = 280.00;
    cub->dire.down = 0.00;
	cub->dire.up = 0.00;
	cub->dire.left = 0.00;
	cub->dire.right = 0.00;
    cub->virtical_num = cub->width;// nb characters
    cub->horizontal_num= cub->height; //nb lignes
	

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
	cub->FOV = 60.00;
	cub->NB_rays = W_WIDTH;
	cub->looking_angle = cub->p.vect.pos - ((double)cub->FOV / 2.00);
	//printf("first lokking angle = %d\n", cub->looking_angle);
	cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);
	i = 0;
	while (i < cub->NB_rays)
	{
		init_ray(cub, &cub->raycast[i], cub->looking_angle);
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

void init_ray(t_struct *cub, t_ray *raycast, double looking_angle)
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
int main(int ac, char **av)
{
    int i;
    i = 0;
    t_struct cub;
    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
    
	ft_read_maps(av[1], &cub);
    //ft_check_alltextures(&cub);
   // ft_check_rgb(&cub);
    //ft_check_map(&cub);
    //cub.mlx_ptr = mlx_init();
	//cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_WIDTH, "cub3D");
    cub.mlx.mlx_ptr = mlx_init();
	cub.mlx.window = mlx_new_window(cub.mlx.mlx_ptr, W_WIDTH, W_HEIGHT, "Souchen_ysmaili'Cub3d");
    //cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	//cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    cub.colorBuffer = (unsigned int **)malloc(W_HEIGHT * sizeof(unsigned int *));
	while (i < W_HEIGHT)
    {
        cub.colorBuffer[i] = (unsigned int *)malloc(W_WIDTH * sizeof(unsigned int));
        i++;

    }
    ft_colorBuffer(&cub);
	cub.img = mlx_new_image(cub.mlx.mlx_ptr, W_WIDTH,  W_HEIGHT);
	// creat mlx texture to display the color buffer
	cub.arrayColor = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    //ft_draw_map(&cub);
    initial(&cub);//normilay find and ft_ray
    find_pos_player(&cub);
    ft_ray(&cub);
	
    //printf("cord = %f\n",cub.p.cord.x );
    raycast(&cub);                                                                                   
    mlx_key_hook(cub.mlx.window, &move, &cub);
	//mlx_hook(cub.mlx.window, 17, 1L << 17, &endgame, &cub);
    mlx_loop(cub.mlx.mlx_ptr);
   
}
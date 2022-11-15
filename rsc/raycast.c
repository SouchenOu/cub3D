/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 08:59:34 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	lets_do_raycast(t_ray *raycast, int x)
{
	double	sostra;
	int		y;
	int		end;
	int		start;

	sostra = degrees_to_radians(raycast->cub->vect.pos) - raycast->ray_looking_angle;
	if (sostra > degrees_to_radians(359.00))
		sostra -= degrees_to_radians(360.00);
	else if (sostra < degrees_to_radians(0.00))
		sostra += degrees_to_radians(360.00);
	raycast->dest = raycast->dest * cos(sostra);
	raycast->h_line = (int)(size_GRID * (1.00 * W_HEIGHT)) / raycast->dest;
	if (raycast->h_line > (1.00 * W_HEIGHT))
		raycast->h_line = (1.00 * W_HEIGHT);
	start = (W_HEIGHT/ 2) - (int)(raycast->h_line / 2.00);
	if (start < 0)
		start = 0;
	end = (W_HEIGHT/ 2) + (int)(raycast->h_line / 2.00);
	if (end >= W_HEIGHT)
		end = W_HEIGHT- 1;
	y = (start - 1);
	while (++y < end)
	{
		raycast->cub->tab[y][x] = 0x8545e6;
		raycast->cub->check = 1;
	}
}


void	raycast(t_struct *cub)
{
	int	i;
    int j;
    i = 0;
	t_ray raycast;

	cub->FOV = 120;
	cub->NB_rays =  W_WIDTH;
	cub->looking_angle = cub->vect.pos - ((double)cub->FOV / 2);
	cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);

	while (i < cub->NB_rays)
	{
		raycast.cub = cub;
		raycast.ray_looking_angle = degrees_to_radians(limite_angle(cub->looking_angle));
		raycast.ray_cordinate.x = -1;
		raycast.ray_cordinate.y = -1;
		raycast.offset.x = -1;
		raycast.offset.y = -1;
		raycast.dir = 0;
		raycast.number_to_check = -2;
		raycast.tang = 0;
		raycast.horizontal_distance = 0;
		raycast.horizontal_cord.y = 0;
		raycast.horizontal_cord.x = 0;
		raycast.virt_cord.x = 0;
		raycast.virt_cord.y = 0;
		raycast.virtical_distance = 0;
        raycast.ray_cord_temp.x = 0;
        raycast.ray_cord_temp.y = 0;
		raycast.dest = 0;
		raycast.h_line = 0;

		
		cub->looking_angle = cub->looking_angle +  (cub->FOV / (double)cub->NB_rays);
        i++;
	}

    //start raycasting
	i = 0;
	if (cub->check)
		ft_tab(cub);
	while (i < cub->NB_rays)
	{
		check_horizontal_vertical(&cub->raycast[i]);
		lets_do_raycast(&cub->raycast[i], i);
        i++;
	}
    i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
        {
            cub->array[i * W_WIDTH + j] = cub->tab[i][j];
            j++;
        }
        i++;
	}
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.window,cub->img, 0, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/17 12:42:23 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	move_player(t_struct *cub)
{
	int	i;

	i = -1;
	cub->looking_angle = cub->p.vect.pos - ((double)cub->FOV / 2.00);
	while (++i < cub->NB_rays)
	{
		cub->raycast[i].ray_looking_angle = degrees_to_radians(limite_angle(cub->looking_angle));
		cub->looking_angle += (cub->FOV / (double)cub->NB_rays);
	}
	mlx_clear_window(cub->mlx.mlx_ptr, cub->mlx.window);
	raycast(cub);
}

int	move(int key, void *param)
{
	t_struct	*cub;

	cub = (t_struct *) param;
	if (key == K_W)
	{
		cub->p.cord.y += (cub->p.vect.y * 5);
		cub->p.cord.x += (cub->p.vect.x * 5);
	}
	else if (key == K_S)
	{
		cub->p.cord.y -= (cub->p.vect.y * 5);
		cub->p.cord.x -= (cub->p.vect.x * 5);
	}
	else if (key == K_AR_R)
	{
		cub->p.vect.pos -= 1;
		cub->p.vect.pos = limite_angle(cub->p.vect.pos);
		cub->p.vect.x = cos(degrees_to_radians(cub->p.vect.pos));
		cub->p.vect.y = -sin(degrees_to_radians(cub->p.vect.pos));
	}
	else if (key == K_AR_L)
	{
		cub->p.vect.pos += 1;
		cub->p.vect.pos = limite_angle(cub->p.vect.pos);
		cub->p.vect.x = cos(degrees_to_radians(cub->p.vect.pos));
		cub->p.vect.y = -sin(degrees_to_radians(cub->p.vect.pos));
	}
	else if (key == K_A)
	{
		cub->p.cord.y += (cub->p.vect.y * 5);
		cub->p.cord.x += (cub->p.vect.x * 5) - 5;
	}
	else if (key == K_D)
	{
		cub->p.cord.y += (cub->p.vect.y * 5);
		cub->p.cord.x += (cub->p.vect.x * 5) + 5;
	}
	find_pos_player(cub);
	move_player(cub);
	return (0);
}
